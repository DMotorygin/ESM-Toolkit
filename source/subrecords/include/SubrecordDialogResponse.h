#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"
#include "SubrecordIntValue.h"

class ESMSubrecordDialogResponseId : public ESMSubrecordStringValue // INAM
{
public:
	ESMSubrecordDialogResponseId(void) {}
	ESMSubrecordDialogResponseId(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordDialogResponseId(void) {}

	virtual const char* GetClassName(void) const { return "Info name string Id"; }
	virtual const char* GetShortName(void) const { return "INAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordDialogResponseId>(void) { return "INAM"; }


class ESMSubrecordDialogResponseIdPrev : public ESMSubrecordStringValue // PNAM
{
public:
	ESMSubrecordDialogResponseIdPrev(void) {}
	ESMSubrecordDialogResponseIdPrev(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordDialogResponseIdPrev(void) {}

	virtual const char* GetClassName(void) const { return "Previous response Id"; }
	virtual const char* GetShortName(void) const { return "PNAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordDialogResponseIdPrev>(void) { return "PNAM"; }


class ESMSubrecordDialogResponseIdNext : public ESMSubrecordStringValue // NNAM
{
public:
    ESMSubrecordDialogResponseIdNext(void) {}
    ESMSubrecordDialogResponseIdNext(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
    virtual ~ESMSubrecordDialogResponseIdNext(void) {}

    virtual const char* GetClassName(void) const { return "Next response Id"; }
    virtual const char* GetShortName(void) const { return "NNAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordDialogResponseIdNext>(void) { return "NNAM"; }



