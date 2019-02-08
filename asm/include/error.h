#ifndef ERROR_H
# define ERROR_H

/*
** USAGE
*/
# define USAGE_OPTS 	"-a: writes an annotated version of the code to stdout."
# define USAGE			"usage: ./asm [-"OPTIONS"] <src_file.s>\n\t" USAGE_OPTS
# define ILLEGAL_OPTION	PROG_NAME "illegal option\n" USAGE

/*
** ERRORS
*/
# define ERR_MALLOC		"Malloc error."
# define ERR_OPEN		"Open error."
# define NO_EXIST		"No such file or directory."
# define PERM_DENIED	"Permission denied."
# define ERR_GNL	    "Unexpected EOF."
# define NO_NAME		"Name was expected in the source file."
# define BIG_NAME		"Name is too long."
# define NO_COMMENT		"Comment was expected in the source file."
# define BIG_COMMENT	"Comment is too long."
# define ERR_QUOTE		"Bad quoting."
# define INVALID_CHAR	"Invalid character."
# define INVALID_TOKEN	"Invalid token."
# define INVALID_OPCODE	"Invalid opcode."
# define INVALID_PARAM	"Invalid parameter."
# define EXPECT_LABEL	"Label name was expected."
# define EXPECT_PARAMS	"Expecting parameters."
# define EXPECT_DIRECT	"Expecting DIRECT parameter."
# define NB_PARAMS		"Wrong number of parameters."
# define CHAMP_TOO_LONG "The code of the champion is too long."
# define NO_LABEL 		"No such label while attempting to dereference."

#endif
