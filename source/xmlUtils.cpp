#include "pch.h"
#include "xmlUtils.h"
#include "string.h"

#include <assert.h>

std::string XMLWriterWrapper::outputFilePath;

XMLWriterWrapper::XMLWriterWrapper(const char* pOutputFilePath)
{
	// initiate xml dumping
	LIBXML_TEST_VERSION
	int res = 0;
	m_pWriter = xmlNewTextWriterDoc(&m_doc, 0);
	m_pWriter = xmlNewTextWriterFilename(pOutputFilePath, 0);
	assert(m_pWriter);

	xmlTextWriterSetIndent(m_pWriter, 1);

	res = xmlTextWriterStartDocument(m_pWriter, NULL, MY_ENCODING, NULL);
	assert(res != -1);
}

XMLWriterWrapper::~XMLWriterWrapper()
{
}

xmlTextWriterPtr XMLWriterWrapper::GetXMLWriter(void)
{
	return XMLWriterWrapper::GetXMLWriterWrapper()->m_pWriter;
}

xmlDocPtr XMLWriterWrapper::GetXMLDoc(void)
{
	return XMLWriterWrapper::GetXMLWriterWrapper()->m_doc;
}

XMLWriterWrapper* XMLWriterWrapper::GetXMLWriterWrapper()
{
#ifdef DUMP_ESM_TO_XML
	if (outputFilePath.empty())
		return nullptr;

	static XMLWriterWrapper instance(outputFilePath.c_str());
	return &instance;
#else
	return nullptr;
#endif
}

/**
 * ConvertInput:
 * @in: string in a given encoding
 * @encoding: the encoding used
 *
 * Converts @in into UTF-8 for processing with libxml2 APIs
 *
 * Returns the converted UTF-8 string, or NULL in case of error.
 */
xmlChar *
ConvertInput(const char *in, const char *encoding)
{
	xmlChar *out;
	int ret;
	int size;
	int out_size;
	int temp;
	xmlCharEncodingHandlerPtr handler;

	if (in == 0)
		return 0;

	handler = xmlFindCharEncodingHandler(encoding);

	if (!handler) {
		printf("ConvertInput: no encoding handler found for '%s'\n",
			encoding ? encoding : "");
		return 0;
	}

	size = (int)strlen(in) + 1;
	out_size = size * 2 - 1;
	out = (unsigned char *)xmlMalloc((size_t)out_size);

	if (out != 0) {
		temp = size - 1;
		ret = handler->input.legacyFunc(out, &out_size, (const xmlChar *)in, &temp);
		if ((ret < 0) || (temp - size + 1)) {
			if (ret < 0) {
				printf("ConvertInput: conversion wasn't successful.\n");
			}
			else {
				printf
				("ConvertInput: conversion wasn't successful. converted: %i octets.\n",
					temp);
			}

			xmlFree(out);
			out = 0;
		}
		else {
			out = (unsigned char *)xmlRealloc(out, out_size + 1);
			out[out_size] = 0;  /*null terminating out */
		}
	}
	else {
		printf("ConvertInput: no mem\n");
	}

	return out;
}
