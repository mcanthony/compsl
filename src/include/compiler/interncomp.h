// $Id:interncomp.h 542 2007-10-01 01:25:23Z tomj $

/*
    CompSL scripting language 
    Copyright (C) 2007  Thomas Jones & John Peberdy

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef INTERNCOMP_H_
#define INTERNCOMP_H_

#include <stdio.h>

#include "node.h"
#include "compsl.h"
#include "intern/gen.h"
#include "intern/bytecode.h"
#include "intern/syms.h"
#include "intern/builtins.h"
#include "intern/compartment.h"


#define CONTINUE_NOOP_IDEN 89
#define BREAK_NOOP_IDEN 90

int yylex( void );
int yyparse(void);


//where the compiler outputs error messages
extern FILE *comp_out;

// Compiler is not reentrant
// TODO: Make compiler reentrant
// Step to make reentrants: 
//   - Find out how to store dynamic vars
//   - Store the three vars below in those vars
extern const char *csl_name;
extern compart *ccompart;
extern char *sprt;
extern int lineNo;

typedef struct _expression_t {
  bool isLiteral;
  bool isFloat;	
  union { 
    int in; 
    float fl; 
    bytecode* bcode; 
  } val;
} expression;


// binops.c
expression* bin_op(int op,expression* a, expression* b);

// functions.c
expression* function_call(const char* name, list *params);

// interncomp.c
bytecode* expr_toBc(expression *exp);
void expr_free(expression* exp);
void expr_ensureLit(expression* exp);
void expr_autocast(bool toFloat,expression *e);
int bc_len(bytecode *);

// var.c
expression *assignVar(const char *str, expression *e);
expression *assignArray(const char *str, bytecode *arrayIndex, expression *e);
expression *readVar(const char* name);
expression *readArray(const char* name, bytecode *arrayIndex);
expression *incVar(const char *name, bool plus, bool post);
expression *incArray(const char *name, bytecode *arIndex, bool plus, bool post);

// control.c
bytecode *ctrlWhile(expression *cond, bytecode *block);
bytecode *ctrlIf(expression *cond, bytecode *block, bytecode *elseBlock);

// err.c
void internalCompileError(const char* str);
void compileError(const char *str);
void compileWarning(const char *str);


/* stackcheck: 
 * 	check code generated by compiler for stack errors
 * 
 * code = code to check
 * codelen = number of bytecodes in code.
 * vm = vm to compile with
 * com = compartment code is compilling with
 * 
 * return value: stack offest at end of code.
 */
int stackcheck(const bytecode *code, int codelen, VM *vm, compart * com);

bytecode *remUselessDUPs(bytecode *code, int codelen, VM *vm, compart * com);

#endif //INTERNCOMP_H_
