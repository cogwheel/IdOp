// IdOp - Custom Operator Library
//
// http://cogwheel.info/idop/
//
// Copyright (c) 2009, Matthew Orlando
//
// See IdOp.h for documentation and license

#ifndef _IDOPCREATE_H_
#define _IDOPCREATE_H_

#include <boost/preprocessor.hpp>
#include "IdOpCreateLeft.h"
#include "IdOpCreateRight.h"


// Creates the global identifier constant and then proceeds to generate the operator templates
#define IDOP_CREATE_BASE(identifier, IdentifierType, primaryOps) \
	enum IdentifierType { identifier }; \
	BOOST_PP_LIST_FOR_EACH_I( \
		IDOP_CREATE_PRIMARY, \
		(identifier, IdentifierType), \
		primaryOps \
	)

#define IDOP_CREATE_PRIMARY(r, idInfo, index, primaryOp) \
	IDOP_CREATE_PRIMARY_BASE( \
		IDOP_TEMPLATE_MACRO(primaryOp), \
		IDOP_PRIMARY_OP(primaryOp), \
		IDOP_IDENTIFIER_CLASS(idInfo), \
		IDOP_INTERMEDIATE_CLASS(idInfo, index), \
		IDOP_OPERATION_LIST(primaryOp) \
	)

#define IDOP_CREATE_PRIMARY_BASE(TEMPLATE, primaryOp, IdentifierClass, IntermediateClass, operations) \
	TEMPLATE(primaryOp, IdentifierClass, IntermediateClass, operations)

#define IDOP_TEMPLATE_MACRO(primaryOp) \
	BOOST_PP_TUPLE_ELEM(3, 0, primaryOp)

#define IDOP_PRIMARY_OP(primaryOp) \
	BOOST_PP_TUPLE_ELEM(3, 1, primaryOp)

#define IDOP_OPERATION_LIST(primaryOp) \
	BOOST_PP_TUPLE_ELEM(3, 2, primaryOp)

#define IDOP_IDENTIFIER_CLASS(idInfo) \
	BOOST_PP_TUPLE_ELEM(2, 1, idInfo)

#define IDOP_INTERMEDIATE_CLASS(idInfo, index) \
	BOOST_PP_CAT(IDOP_IDENTIFIER_CLASS(idInfo), index)


#endif