#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

class chat_message
{
public:

	enum { magic_length = 4 }; // uint32 8 size
	enum { payload_length = 4 };
	enum { header_length = magic_length + payload_length };
	enum { max_body_length = 512 };

	chat_message()
		: body_length_(0)
	{
	}

	const char* data() const
	{
		return data_;
	}

	char* data()
	{
		return data_;
	}

	size_t length() const
	{
		return header_length + body_length_;
	}

	const char* body() const
	{
		return data_ + header_length;
	}

	char* body()
	{
		return data_ + header_length;
	}

	size_t body_length() const
	{
		return body_length_;
	}

	void body_length(size_t new_length)
	{
		body_length_ = new_length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}

	bool decode_header()
	{
		char magic[magic_length + 1] = "";
		auto size = sizeof(Magic);
		strncat(magic, data_, magic_length);
		//uint32_t* m1 = (uint32_t*)magic;
		assert(Parse<uint32_t>(magic) == DefaultMagic);

		char payloadSize[payload_length + 1] = "";
		strncat(payloadSize, data_ + magic_length, payload_length);
		body_length_ = Parse<uint32_t>(payloadSize);
		
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}
		return true;
	}

	void encode_header()
	{
		memcpy(data_, &chat_message::DefaultMagic, magic_length);
		memcpy(data_ + magic_length, &body_length_, payload_length);
	}

	uint32_t toUint(char(&buffer)[4], size_t x)
	{
		auto i = *reinterpret_cast<unsigned int *>(buffer + x);

		i =  *reinterpret_cast<unsigned int *>(&buffer[x]);
	}

	void SerializeInt32(char(&buf)[4], int32_t val)
	{
		std::memcpy(buf, &val, 4);
	}

	template<typename T>
	T Parse(const char(&buf)[5])
	{
		T val;
		std::memcpy(&val, buf, 4);
		return val;
	}

	template<typename T>
	T Serialize(void* data, size_t num)
	{
		T val;
		std::memcpy(&val, buf, 4);
		return val;
	}

	static uint32_t DefaultMagic;

private:
	char data_[header_length + max_body_length];
	size_t body_length_;


	uint32_t Magic = 0;

};


uint32_t chat_message::DefaultMagic = 0x9E2B83C1;