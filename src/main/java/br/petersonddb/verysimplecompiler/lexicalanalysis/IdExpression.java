/**
 * 
 * The very simple compiler project, 2018.
 * 
 * Written by Peterson D. de Bem.
 * 
 */

package br.petersonddb.verysimplecompiler.lexicalanalysis;

/** 
 * This class defines the id expression.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public class IdExpression extends Expression {

    /**
     * Constructs a new IdExpression with a regex to identify identifier tokens
     */
    public IdExpression() {
        super("[a-zA-Z][a-zA-Z0-9]*", Token.TOKEN_ID);
    }

}