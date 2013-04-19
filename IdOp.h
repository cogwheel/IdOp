// IdOp v1.0.1 - Custom Operator Library
//
// http://cogwheel.info/idop/
//
// Copyright (c) 2009, Matthew Orlando
//
// All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.



// TODO documentation



#ifndef _IDOP_H_
#define _IDOP_H_

#include "IdOpCreate.h"

// Create a monomorphic operator (no other operators can be made with the same identifier)
// leftOp must have higher or equal precedence relative to rightOp
// Return type defaults to the type of the left operand at the point of use
#define IDOP_CREATE_LEFT_HANDED(leftOp, identifier, rightOp, OperationType) \
	IDOP_CREATE_LEFT_HANDED_RET(leftOp, identifier, rightOp, OperationType, IDOP_OPERAND_TYPE)

// Create a monomorphic operator (no other operators can be made from the same identifier)
// rightOp must have higher (not equal) precedence relative to leftOp
// Return type defaults to the operand type.
#define IDOP_CREATE_RIGHT_HANDED(leftOp, identifier, rightOp, OperationType) \
	IDOP_CREATE_RIGHT_HANDED_RET(rightOp, identifier, leftOp, OperationType, IDOP_OPERAND_TYPE)

// Create a monomorphic operator (no other operators can be made with the same identifier)
// leftOp must have higher or equal precedence relative to rightOp
#define IDOP_CREATE_LEFT_HANDED_RET(leftOp, identifier, rightOp, OperationType, RetType) \
	IDOP_CREATE( identifier, \
		IDOP_LEFT_HANDED(leftOp, \
			IDOP_OPERATION_RET(rightOp, OperationType, RetType) \
		) \
	)

// Create a single (exclusive) operator for the identifier.
// rightOp must have higher precedence relative to leftOp
#define IDOP_CREATE_RIGHT_HANDED_RET(leftOp, identifier, rightOp, OperationType, RetType) \
	IDOP_CREATE( identifier, \
		IDOP_RIGHT_HANDED(leftOp, \
			IDOP_OPERATION_RET(rightOp, OperationType, RetType) \
		) \
	)

// Creates template classes, operator overloads, and global constants to implement a custom operator
#define IDOP_CREATE(identifier, primaryOps) \
	IDOP_CREATE_BASE( \
		identifier, \
		BOOST_PP_CAT(IdOpIdentifier, identifier), \
		BOOST_PP_TUPLE_TO_LIST(BOOST_PP_SEQ_SIZE(primaryOps), BOOST_PP_SEQ_TO_TUPLE(primaryOps)) \
	)

// Create a polymorphic operation (multiple operations using the same identifier)
#define IDOP_OPERATION_RET(op, OperationType, RetType) \
	((op, OperationType, RetType))

// Create an operation
// Assumes the operation returns the same type as the operands
#define IDOP_OPERATION(op, OperationType) \
	((op, OperationType, IDOP_OPERAND_TYPE))

// Create a left-handed set of operations
// leftOp must have higher or equal precedence relative to all the given operations
#define IDOP_LEFT_HANDED(op, operations) \
	((IDOP_CREATE_LEFT_PRIMARY_TEMPLATES, op, operations))

// Create a right-handed set of operations
// rightOp must have higher or equal precedence relative to all the given operations
#define IDOP_RIGHT_HANDED(op, operations) \
	((IDOP_CREATE_RIGHT_PRIMARY_TEMPLATES, op, operations))


#endif // _IDOP_H_
