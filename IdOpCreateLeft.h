// IdOp - Custom Operator Library
//
// http://cogwheel.info/idop/
//
// Copyright (c) 2009, Matthew Orlando
//
// See IdOp.h for documentation and license

#ifndef _IDOPCREATELEFT_H_
#define _IDOPCREATELEFT_H_

#include "IdOpCreateCommon.h"

#define IDOP_CREATE_LEFT_PRIMARY_TEMPLATES(primaryOp, IdentifierClass, IntermediateClass, operations) \
	IDOP_CREATE_PRIMARY_TEMPLATES( \
		IntermediateClass, \
		operations, \
		IDOP_LEFT_OPERATION_LIST(operations), \
		IDOP_LEFT_GLOBAL_SIGNATURE(primaryOp, IdentifierClass) \
	)

#define IDOP_LEFT_OPERATION_LIST_ITEM(r, d, index, operation) \
	IDOP_GET_RETURN_TYPE(operation) operator IDOP_GET_OPERATOR(operation)(const OperandType& other) const \
	{ return IDOP_OPERATION_OBJECT_MEMBER(index)(_obj, other); } \

#define IDOP_LEFT_OPERATION_LIST(operations) \
	BOOST_PP_SEQ_FOR_EACH_I(IDOP_LEFT_OPERATION_LIST_ITEM, , operations)

#define IDOP_LEFT_GLOBAL_SIGNATURE(primaryOp, IdentifierClass) \
	operator primaryOp(const OperandType& primary, IdentifierClass identifier)


#endif
