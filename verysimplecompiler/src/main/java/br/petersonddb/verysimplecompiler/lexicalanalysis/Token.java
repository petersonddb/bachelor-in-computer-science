/**
 * 
 * The very simple compiler project, 2018.
 * 
 * Written by Peterson D. de Bem.
 * 
 */

package br.petersonddb.verysimplecompiler.lexicalanalysis;

/** 
 * This class defines tokens representation.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public class Token {

    /**
     * Possible token types
     */
    public static final int TOKEN_NULL = 0, TOKEN_ID = 1, TOKEN_NUMBER = 2;

    private final int type;
    private final String lexeme;

    /**
     * Constructs a token with the specified type and lexeme
     * @param type the token type
     * @param lexeme the token lexeme
     */
    public Token(int type, String lexeme) {
        this.type = type;
        this.lexeme = lexeme;
    }

    /**
     * Returns the token's type
     * @return the token's type
     */
    public int getType() { return type; }

    /**
     * Returns the token's value
     * @return the token's value
     */
    public String getLexeme() { return lexeme; }

}
