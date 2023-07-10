
#pragma once
#include "pch.h"
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#if defined(LIBXML_WRITER_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
#define MY_ENCODING "UTF-8" //"ISO-8859-1"
#endif

//#ifdef _DEBUG
#define DUMP_ESM_TO_XML
//#endif

class XMLWriterWrapper
{
public:
	~XMLWriterWrapper(void);

	static void SetXMLWriterOutputFile(const std::string& in) { outputFilePath = in; }

	static XMLWriterWrapper* GetXMLWriterWrapper(void);
	static xmlTextWriterPtr GetXMLWriter(void);
	static xmlDocPtr GetXMLDoc(void);

	void operator=(XMLWriterWrapper const&) = delete;
	XMLWriterWrapper(XMLWriterWrapper const&) = delete;

protected:
	XMLWriterWrapper(const char* pOutputFilePath);

	xmlTextWriterPtr m_pWriter;
	xmlDocPtr m_doc;

	static std::string outputFilePath;
};

// this function is taken from libxml writer example 
xmlChar* ConvertInput(const char *in, const char *encoding);

// get int as hex
template<typename T>
std::string int_to_hex(T i)
{//std::showbase  "0x"
	std::stringstream stream;
	stream
		<< "0x"
		<< std::hex
		<< std::setfill('0') 
		<< std::setw(sizeof(T) * 2)
		<< i;
	return stream.str();
}

#define LOG_VAR_AS_STR(name, var) res = xmlTextWriterWriteAttribute(writer, BAD_CAST name, BAD_CAST std::to_string(var).c_str());	assert(res != -1);
#define LOG_CHAR_AS_INT(name, var) res = xmlTextWriterWriteAttribute(writer, BAD_CAST name, BAD_CAST std::to_string((int)var).c_str());	assert(res != -1);
#define LOG_VAR_AS_HEX(name, var) res = xmlTextWriterWriteAttribute(writer, BAD_CAST name, BAD_CAST int_to_hex(var).c_str());	assert(res != -1);


