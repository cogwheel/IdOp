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
		IntermediateClass, \
		operations, \
		IDOP_RIGHT_OPERATION_LIST(operations, IntermediateClass), \
		IDOP_RIGHT_GLOBAL_SIGNATURE(primaryOp, IdentifierClass) \
	)

#define IDOP_RIGHT_OPERATION_LIST_ITEM(r, opInfo, index, operation) \
	friend IDOP_GET_RETURN_TYPE(operation) operator IDOP_GET_OPERATOR(operation) ( \
		const OperandType& left, \
		const IDOP_GET_RIGHT_PARAM_TYPE(opInfo)& right \
	) \
	{ return right.IDOP_OPERATION_OBJECT_MEMBER(index)(left, right._obj); }

#define IDOP_ENUM_CAT_I(z, index, text) BOOST_PP_CAT(text, index)

#define IDOP_RIGHT_FRIEND_TEMPLATE_PARAMS(operations) \
	BOOST_PP_ENUM_TRAILING(BOOST_PP_SEQ_SIZE(operations), IDOP_ENUM_CAT_I, OperatorType)

#define IDOP_GET_RIGHT_PARAM_TYPE(opInfo) \
	BOOST_PP_TUPLE_ELEM(2, 1, opInfo) < \
		OperandType \
		IDOP_RIGHT_FRIEND_TEMPLATE_PARAMS(BOOST_PP_TUPLE_ELEM(2, 0, opInfo)) \
	>

#define IDOP_RIGHT_OPERATION_LIST(operations, IntermediateClass) \
	BOOST_PP_SEQ_FOR_EACH_I(IDOP_RIGHT_OPERATION_LIST_ITEM, (operations, IntermediateClass), operations)

#define IDOP_RIGHT_GLOBAL_SIGNATURE(primaryOp, IdentifierClass) \
	operator primaryOp(IdentifierClass identifier, const OperandType& primary)

#endif
