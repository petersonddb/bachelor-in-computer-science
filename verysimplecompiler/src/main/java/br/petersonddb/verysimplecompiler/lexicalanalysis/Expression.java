/**
 * 
 * The very simple compiler project, 2018.
 * 
 * Written by Peterson D. de Bem.
 * 
 */

package br.petersonddb.verysimplecompiler.lexicalanalysis;

import java.io.IOException;

/** 
 * This class defines the Expression abstraction.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public abstract class Expression {
    
    /**
     * The tokens type of this expression generated tokens
     */
    private final int TOKEN_TYPE;
    
    /**
     * The regular expression which describes the token pattern
     */
    private final String REGEX;

    /**
     * Constructs a expression with the specified regular expression
     * @param regex the regular expression which describes the token pattern of this expression generated tokens
     * @param tokenType the tokens type of this expression generated tokens
     */
    public Expression(String regex, int tokenType) {
        REGEX = regex;
        TOKEN_TYPE = tokenType;
    }

    /**
     * Interprets the stream at the scanner context input
     * @param context the scanner context
     * @return the next token at the input stream or null if the input does not match this expression pattern
     * @throws IOException If an I/O error occurs when reading from the input stream
     */
    public Token interpret(ScannerContext context) throws IOException {
        Token t = null;
        removeWs(context);
        if(context.read() != -1) {
            if(context.getCurrent().matches(REGEX)) {
                while(context.read() != -1)
                    if(!context.getCurrent().matches(REGEX)) {
                        context.unread();
                        break;
                    }
                t = new Token(TOKEN_TYPE, context.getCurrent());
                context.rebase();
            } else
                context.unread();
        }
        return t;
    }

    /**
     * Remove the next white spaces from the scanner context input stream
     * @param context the scanner context
     * @throws IOException If an I/O error occurs when reading from the input stream
     */
    public void removeWs(ScannerContext context) throws IOException {
        char c;
        while((c = context.read()) != -1)
            if(c != ' ') {
                context.unread();
                context.rebase();
                break;
            }
    }

}