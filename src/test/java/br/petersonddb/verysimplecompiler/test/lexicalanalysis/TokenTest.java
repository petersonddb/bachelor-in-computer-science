/**
 * 
 * The very simple compiler project, 2018.
 * 
 * Written by Peterson D. de Bem, 2018.
 * 
 */

package br.petersonddb.verysimplecompiler.test.lexicalanalysis;

import br.petersonddb.verysimplecompiler.lexicalanalysis.Token;

import junit.framework.TestCase;
import junit.framework.TestSuite;
import junit.framework.Test;

/** 
 * This class defines the token tests.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public class TokenTest extends TestCase {

    /**
     * Fixture
     */
    private Token token;

    /**
     * Values to test tokens
     */
    private int type;
    private String lexeme;

    /**
     * Initializes the test fixture
     */
    @Override
    protected void setUp() {
        type = Token.TOKEN_ID;
        lexeme = "BigBee";
        token = new Token(type, lexeme);
    }

    /**
     * Test suite
     * @return a test to be executed
     */
    public static Test suite() {
        return new TestSuite(TokenTest.class);
    }

    /**
     * Tests if the token values are correctly atributed
     */
    public void testTokenValues() {
        assertEquals(type, token.getType());
        assertEquals(lexeme, token.getLexeme());
    }

}
