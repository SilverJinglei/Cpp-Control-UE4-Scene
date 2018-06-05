#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

#include <deque>
#include <iostream>
#include <thread>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>

#include "UE4_Request.h"
#include "example.h"


using boost::asio::ip::tcp;
using namespace std;

typedef std::deque<UE4_Request> chat_message_queue;

class Terminal
{
public:
	Terminal(boost::asio::io_context& io_context,
		const tcp::resolver::results_type& endpoints)
		: io_context_(io_context),
		socket_(io_context)
	{
		do_connect(endpoints);
	}
	
	~Terminal()
	{
		Close();
	}

	void Send(const UE4_Request& msg)
	{
		boost::asio::post(io_context_,
			[this, msg]()
		{
			bool write_in_progress = !write_msgs_.empty();
			write_msgs_.push_back(msg);
			if (!write_in_progress)
			{
				do_write();
			}
		});
	}

	void Close()
	{
		boost::asio::post(io_context_, [this]() { socket_.close(); });
	}

private:
	void do_connect(const tcp::resolver::results_type& endpoints)
	{
		boost::asio::async_connect(socket_, endpoints,
			[this](boost::system::error_code ec, tcp::endpoint)
		{
			if (!ec)
			{
				do_read_header();
			}
		});
	}

	void do_read_header()
	{
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), UE4_Request::header_length),
			[this](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec && read_msg_.decode_header())
			{
				if(read_msg_.body_length() > 0)
					do_read_body();
			}
			else
			{
				socket_.close();
			}
		});
	}

	void do_read_body()
	{
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
			[this](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				std::cout.write(read_msg_.body(), read_msg_.body_length());
				std::cout << "\n";



				do_read_header();
			}
			else
			{
				socket_.close();
			}
		});
	}

	void do_write()
	{
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().data(),
				write_msgs_.front().length()),
			[this](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				write_msgs_.pop_front();
				if (!write_msgs_.empty())
				{
					do_write();
				}
			}
			else
			{
				socket_.close();
			}
		});
	}

private:
	boost::asio::io_context& io_context_;
	tcp::socket socket_;
	UE4_Request read_msg_;
	chat_message_queue write_msgs_;
};

class Station
{
public:

	Station()
	{
		tcp::resolver resolver(io_context);
		const auto endpoints = resolver.resolve("127.0.0.1", "9000");//(argv[1], argv[2]);
		
		InTerminal = new Terminal(io_context, endpoints);
	}

	~Station()
	{
		delete InTerminal;
	}

private:

	boost::asio::io_context io_context;

public:
	Terminal* InTerminal;
	std::thread* BackgroundWorker;

	void Launch()
	{
		BackgroundWorker = new std::thread([this]() { io_context.run(); });

		BackgroundWorker->detach();
		//t.join();
	}

	int msgId = 1001;
	std::ostringstream ostr;
	string raw_message;

	void InvokeRemote(const string& line) {
		ostr << msgId << ":" << line;
		raw_message = ostr.str();

		UE4_Request msg;

		msg.body_length(raw_message.length());
		std::memcpy(msg.body(), raw_message.c_str(), msg.body_length());
		msg.encode_header();
		InTerminal->Send(msg);

		msgId++;
		ostr.str("");
	}

	void Close()
	{
		InTerminal->Close();
	}
};

class UE4Proxy
{
public:

	UE4Proxy()
	{
		_station = new Station();
	}

	~UE4Proxy()
	{
		delete _station;
	}

	void Establish() {
		_station->Launch();
	}

public:
	void vget(string cmd) {
		_station->InvokeRemote("vget " + cmd);
	}

	void vset(string cmd) {
		_station->InvokeRemote("vset " + cmd);
	}


	FRotator vgetObjectRotation(const string& actor) 
	{
		auto cmd = R"(/object/)" + actor + R"(/rotation)";

		vget(cmd);

		FRotator r = { 1.0, 10, 0 };
		return r;
	}
	
	const char space = ' ';

	template<typename... T>
	void vexec(string blueprintName, string methodName, T... args) {

		string cmd = "vexec";
		cmd += (space + blueprintName);
		cmd += (space + methodName);

		std::initializer_list<int>{([&] {cmd += (space + args); }(), 0)...};

		_station->InvokeRemote(cmd);
	}

	void vrun() {

	}


protected:
	
	Station * _station;
private:
};

class RobotAPI : public UE4Proxy
{
public:

	RobotAPI()
	{
	}

	~RobotAPI()
	{
	}

public:
	void MotorOnForDegrees(const string& robotId, int motorIndex, float degree, float speed)
	{
		char buff[100];
		//snprintf(buff, sizeof(buff), "%d ", motorIndex, );
		string buffAsStdStr = buff;

		vexec(robotId, string("MotorOnForDegrees"),
			std::to_string(motorIndex), 
			std::to_string(degree), 
			std::to_string(speed));
	}
};


void RawRobotAPI()
{
	char line[UE4_Request::max_body_length + 1];

	std::ostringstream ostr;
	string raw_message;

	Station s;
	s.Launch();

	while (std::cin.getline(line, UE4_Request::max_body_length + 1))
	{
		s.InvokeRemote(line);
	}

	s.Close();
	//s.BackgroundWorker->join();
}


int main(int argc, char* argv[])
{
	try
	{
		RobotAPI robot;
		robot.Establish();

		std::this_thread::sleep_for(std::chrono::seconds(1));

		robot.MotorOnForDegrees("KukaBP", 0, -180, 58);
		
		robot.vgetObjectRotation("Joint1");

		char line[UE4_Request::max_body_length + 1];
		std::cin.getline(line, UE4_Request::max_body_length + 1);


		//RawRobotAPI();

	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}


//int main()
//{
//	using namespace boost::lambda;
//	typedef std::istream_iterator<int> in;
//
//	std::for_each(
//		in(std::cin), in(), std::cout << (_1 * 3) << " ");
//}