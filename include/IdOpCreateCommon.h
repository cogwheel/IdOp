// IdOp - Custom Operator Library
//
// http://cogwheel.info/idop/
//
// Copyright (c) 2009, Matthew Orlando
//
// See IdOp.h for documentation and license

#ifndef _IDOPCREATECOMMON_H_
#define _IDOPCREATECOMMON_H_

#define IDOP_CREATE_PRIMARY_TEMPLATES( \
		primaryOp, \
		IdentifierClass, \
		IntermediateClass, \
		operations, \
		OPERATION_MEMBERS, \
		GLOBAL_SIG \
	) \
	IDOP_CREATE_PRIMARY_TEMPLATES_BASE( \
		primaryOp, \
		IdentifierClass, \
		,  \
		IntermediateClass, \
		operations, \
		OPERATION_MEMBERS, \
		GLOBAL_SIG \
	) \
	IDOP_CREATE_PRIMARY_TEMPLATES_BASE( \
		primaryOp, \
		IdentifierClass, \
		const, \
		BOOST_PP_CAT(Const, IntermediateClass), \
		operations, \
		OPERATION_MEMBERS, \
		GLOBAL_SIG \
	)

#define IDOP_CREATE_PRIMARY_TEMPLATES_BASE( \
		primaryOp, \
		IdentifierClass, \
		constQualifier, \
		IntermediateClass, \
		operations, \
		OPERATION_MEMBERS, \
		GLOBAL_SIG \
	) \
	template< \
		typename IDOP_OPERAND_TYPE \
		IDOP_TYPENAME_LIST(operations) \
	> \
	class IntermediateClass { \
	public: \
		IntermediateClass( \
			constQualifier IDOP_OPERAND_TYPE& obj \
			IDOP_CTOR_PARAM_LIST(operations) \
		)  \
		: _obj(obj) \
		IDOP_CTOR_INIT_LIST(operations) \
		{ } \
		OPERATION_MEMBERS(operations, IntermediateClass) \
	private: \
		constQualifier IDOP_OPERAND_TYPE& _obj; \
		IDOP_OBJECT_MEMBER_LIST(operations) \
	}; \
	template<typename IDOP_OPERAND_TYPE> \
	inline IntermediateClass< \
		IDOP_OPERAND_TYPE \
		IDOP_OPERATION_TYPE_LIST(operations) \
	> \
	GLOBAL_SIG(primaryOp, IdentifierClass, constQualifier) \
	{ \
		IDOP_OPERATION_CONSTANT_LIST(operations) \
		return IntermediateClass< \
			IDOP_OPERAND_TYPE \
			IDOP_OPERATION_TYPE_LIST(operations) \
		> \
		( \
			primary \
			IDOP_CTOR_ARGUMENT_LIST(operations) \
		); \
	}


#define IDOP_OPERATION_TYPENAME(index) BOOST_PP_CAT(IDOP_OPERATOR_TYPE, index)
#define IDOP_OPERATION_OBJECT_PARAM(index) BOOST_PP_CAT(op, index)
#define IDOP_OPERATION_OBJECT_MEMBER(index) BOOST_PP_CAT(_, IDOP_OPERATION_OBJECT_PARAM(index))

#define IDOP_GET_OPERATOR(operation) BOOST_PP_TUPLE_ELEM(3, 0, operation)
#define IDOP_GET_OPERATION_TYPE(operation) BOOST_PP_TUPLE_ELEM(3, 1, operation)<IDOP_OPERAND_TYPE>
#define IDOP_GET_RETURN_TYPE(operation) BOOST_PP_TUPLE_ELEM(3, 2, operation)

#define IDOP_TYPENAME_LIST(operations) \
	BOOST_PP_ENUM_TRAILING(BOOST_PP_SEQ_SIZE(operations), IDOP_CLASS_TYPENAME_LIST_ITEM, )

#define IDOP_CLASS_TYPENAME_LIST_ITEM(z, index, t) \
	typename IDOP_OPERATION_TYPENAME(index)

#define IDOP_CTOR_PARAM_LIST(operations) \
	BOOST_PP_ENUM_TRAILING(BOOST_PP_SEQ_SIZE(operations), IDOP_CTOR_PARAM_LIST_ITEM, )

#define IDOP_CTOR_PARAM_LIST_ITEM(z, index, o) \
	const IDOP_OPERATION_TYPENAME(index)& IDOP_OPERATION_OBJECT_PARAM(index) \

#define IDOP_CTOR_INIT_LIST(operations) \
	BOOST_PP_ENUM_TRAILING(BOOST_PP_SEQ_SIZE(operations), IDOP_CTOR_INIT_LIST_ITEM, )

#define IDOP_CTOR_INIT_LIST_ITEM(z, index, o) \
	IDOP_OPERATION_OBJECT_MEMBER(index)(IDOP_OPERATION_OBJECT_PARAM(index)) \

#define IDOP_OBJECT_MEMBER_LIST(operations) \
	BOOST_PP_SEQ_FOR_EACH_I(IDOP_OBJECT_MEMBER_LIST_ITEM, , operations)

#define IDOP_OBJECT_MEMBER_LIST_ITEM(r, d, index, o) \
	const IDOP_OPERATION_TYPENAME(index)& IDOP_OPERATION_OBJECT_MEMBER(index);

#define IDOP_OPERATION_TYPE_LIST(operations) \
	BOOST_PP_SEQ_FOR_EACH_I(IDOP_OPERATION_TYPE_LIST_ITEM, , operations)

#define IDOP_OPERATION_TYPE_LIST_ITEM(r, d, i, operation) \
	, IDOP_GET_OPERATION_TYPE(operation) \

#define IDOP_OPERATION_CONSTANT_LIST(operations) \
	BOOST_PP_SEQ_FOR_EACH_I(IDOP_OPERATION_CONSTANT_LIST_ITEM, , operations)

#define IDOP_OPERATION_CONSTANT_LIST_ITEM(r, d, index, operation) \
	const IDOP_GET_OPERATION_TYPE(operation) IDOP_OPERATION_OBJECT_MEMBER(index) \
		= IDOP_GET_OPERATION_TYPE(operation)();

#define IDOP_CTOR_ARGUMENT_LIST(operations) \
	BOOST_PP_ENUM_TRAILING(BOOST_PP_SEQ_SIZE(operations), IDOP_CTOR_ARGUMENT_LIST_ITEM, )

#define IDOP_CTOR_ARGUMENT_LIST_ITEM(z, index, o) \
	IDOP_OPERATION_OBJECT_MEMBER(index)


#endif
