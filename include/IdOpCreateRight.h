// IdOp - Custom Operator Library
//
// http://cogwheel.info/idop/
//
// Copyright (c) 2009, Matthew Orlando
//
// See IdOp.h for documentation and license

#ifndef _IDOPCREATERIGHT_H_
#define _IDOPCREATERIGHT_H_

#include "IdOpCreateCommon.h"

#define IDOP_CREATE_RIGHT_PRIMARY_TEMPLATES(primaryOp, IdentifierClass, IntermediateClass, operations) \
	IDOP_CREATE_PRIMARY_TEMPLATES( \
		primaryOp, \
		IdentifierClass, \
		IntermediateClass, \
		operations, \
		IDOP_RIGHT_OPERATION_LIST, \
		IDOP_RIGHT_GLOBAL_SIGNATURE \
	)

#define IDOP_RIGHT_OPERATION_LIST(operations, IntermediateClass) \
	BOOST_PP_SEQ_FOR_EACH_I(IDOP_RIGHT_OPERATION_LIST_ITEM, (operations, IntermediateClass), operations)

#define IDOP_RIGHT_OPERATION_LIST_ITEM(r, opInfo, index, operation) \
	IDOP_RIGHT_OPERATION_LIST_ITEM_BASE(operation, , opInfo, index) \
	IDOP_RIGHT_OPERATION_LIST_ITEM_BASE(operation, const, opInfo, index)

#define IDOP_RIGHT_OPERATION_LIST_ITEM_BASE(operation, constQualifier, opInfo, index) \
	friend IDOP_GET_RETURN_TYPE(operation) operator IDOP_GET_OPERATOR(operation) ( \
		constQualifier IDOP_OPERAND_TYPE& left, \
		const IDOP_GET_RIGHT_PARAM_TYPE(opInfo)& right \
	) \
	{ return right.IDOP_OPERATION_OBJECT_MEMBER(index)(left, right._obj); }

#define IDOP_RIGHT_GLOBAL_SIGNATURE(primaryOp, IdentifierClass, constQualifier) \
	operator primaryOp(IdentifierClass identifier, constQualifier IDOP_OPERAND_TYPE& primary)

#define IDOP_ENUM_CAT_I(z, index, text) BOOST_PP_CAT(text, index)

#define IDOP_RIGHT_FRIEND_TEMPLATE_PARAMS(operations) \
	BOOST_PP_ENUM_TRAILING(BOOST_PP_SEQ_SIZE(operations), IDOP_ENUM_CAT_I, IDOP_OPERATOR_TYPE)

#define IDOP_GET_RIGHT_PARAM_TYPE(opInfo) \
	BOOST_PP_TUPLE_ELEM(2, 1, opInfo) < \
		IDOP_OPERAND_TYPE \
		IDOP_RIGHT_FRIEND_TEMPLATE_PARAMS(BOOST_PP_TUPLE_ELEM(2, 0, opInfo)) \
	>

#endif
