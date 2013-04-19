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
		primaryOp, \
		IdentifierClass, \
		IntermediateClass, \
		operations, \
		IDOP_LEFT_OPERATION_LIST, \
		IDOP_LEFT_GLOBAL_SIGNATURE \
	)

#define IDOP_LEFT_OPERATION_LIST(operations, intermediateClass) \
	BOOST_PP_SEQ_FOR_EACH_I(IDOP_LEFT_OPERATION_LIST_ITEM, , operations)

#define IDOP_LEFT_GLOBAL_SIGNATURE(primaryOp, IdentifierClass, constQualifier) \
	operator primaryOp(constQualifier IDOP_OPERAND_TYPE& primary, IdentifierClass identifier)

#define IDOP_LEFT_OPERATION_LIST_ITEM(r, d, index, operation) \
	IDOP_LEFT_OPERATION_LIST_ITEM_BASE(index, operation, ) \
	IDOP_LEFT_OPERATION_LIST_ITEM_BASE(index, operation, const)

#define IDOP_LEFT_OPERATION_LIST_ITEM_BASE(index, operation, constQualifier) \
	IDOP_GET_RETURN_TYPE(operation) operator IDOP_GET_OPERATOR(operation) \
	(constQualifier IDOP_OPERAND_TYPE& other) const \
	{ return IDOP_OPERATION_OBJECT_MEMBER(index)(_obj, other); }

#endif
