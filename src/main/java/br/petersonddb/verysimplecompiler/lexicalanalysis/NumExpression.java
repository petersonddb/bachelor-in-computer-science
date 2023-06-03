/**
 * 
 * The very simple compiler project, 2018.
 * 
 * Written by Peterson D. de Bem.
 * 
 */

package br.petersonddb.verysimplecompiler.lexicalanalysis;

/** 
 * This class defines the num expression.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public class NumExpression extends Expression {

    /**
     * Constructs a new NumExpression with a regex to identify number tokens
     */
    public NumExpression() {
        super("[0-9]+", Token.TOKEN_NUMBER);
    }

}