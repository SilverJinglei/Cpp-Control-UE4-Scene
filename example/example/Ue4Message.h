#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

class chat_message
{
public:

	enum { magic_length = 8 }; // uint32 8 size
	enum { header_length = 12 };
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
		strncat(magic, data_, magic_length);
		//assert(atoi(magic) == DefaultMagic);

		char header[header_length + 1] = "";
		strncat(header, data_, header_length - magic_length);
		body_length_ = atoi(header);
		
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}
		return true;
	}

	void encode_header()
	{
		char magic[magic_length + 1] = "";
		sprintf(magic, "%08x", chat_message::DefaultMagic);
		memcpy(data_, magic, magic_length);


		char header[header_length - magic_length + 1] = "";
		sprintf_s(header, "%4d", static_cast<int>(body_length_));
		memcpy(data_ + magic_length, header, header_length - magic_length);
	}

	static uint32_t DefaultMagic;

private:
	char data_[header_length + max_body_length];
	size_t body_length_;


	uint32_t Magic = 0;

};


uint32_t chat_message::DefaultMagic = 0x9E2B83C1;