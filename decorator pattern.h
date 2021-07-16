#pragma once
#include "stdc++.h"
#include "iuser.h"

class Stream
{
public:
	virtual ~Stream() {}
	virtual void Read(int number) = 0;
	virtual void Write(int position) = 0;
};

class FileStream : public Stream
{
public:
	virtual void Read(int number) override
	{
		cout << "read file stream!" << endl;
	}
	virtual void Write(int position)
	{
		cout << "write file stream!" << endl;
	}
};

class NetStream : public Stream
{
public:
	virtual void Read(int number) override
	{
		cout << "read netework stream!" << endl;
	}
	virtual void Write(int position)
	{
		cout << "write network stream!" << endl;
	}
};

class DecoratorBase : public Stream
{
protected:
	Stream* m_stream;
public:
	virtual ~DecoratorBase() {}
	virtual void SomeOption() = 0;
	DecoratorBase(Stream* stream) : m_stream(stream) {}
};

class CryptDecorator : public DecoratorBase
{
public:
	CryptDecorator(Stream* stream) : DecoratorBase(stream) {}
	virtual void SomeOption() override
	{
		cout << "CryptDecorator's Option!" << endl;
	}

	virtual void Read(int number) override
	{
		cout << "Encrypt Stream!" << endl;
		m_stream->Read(number);
	}

	virtual void Write(int position) override
	{
		cout << "Decrypt Stream!" << endl;
		m_stream->Write(position);
	}
};

class XDecorator : public DecoratorBase
{
public:
	XDecorator(Stream* stream) : DecoratorBase(stream) {}
	virtual void SomeOption() override
	{
		cout << "XDecorator's Option!" << endl;
	}

	virtual void Read(int number) override
	{
		cout << "XXXX Stream!" << endl;
		m_stream->Read(number);
	}

	virtual void Write(int position) override
	{
		cout << "XXXX Stream!" << endl;
		m_stream->Write(position);
	}
};


/* use the pattern */
class DecoratorPatternPublisher final : public IPublisher
{
public:
	virtual void UsePattern() override
	{
		cout << "===============>>>>>>> Test Decorator Pattern <<<<<<<===============\n";

		cout << "\n---------Componet with Decorator----------\n";
		FileStream* fileStream = new FileStream();
		fileStream->Read(1);
		fileStream->Write(2);
		CryptDecorator* cryptFile = new CryptDecorator(fileStream);
		cryptFile->Read(1);
		cryptFile->Write(2);

		cout << "\n---------Decorator with Decorator---------\n";
		XDecorator* XCryptFile = new XDecorator(cryptFile);
		XCryptFile->Read(1);
		XCryptFile->Write(2);

		delete XCryptFile;
		delete cryptFile;
		delete fileStream;
	}
};