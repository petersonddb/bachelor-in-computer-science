/**
 * 
 * The very simple compiler project, 2018.
 * 
 * Written by Peterson D. de Bem.
 * 
 */

package br.petersonddb.verysimplecompiler.lexicalanalysis;

import java.util.ArrayList;
import java.util.List;

import java.io.IOException;

/** 
 * This class defines the simple scanner.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public class SimpleScanner extends Scanner {

    /**
     * A buffer to keep the latest found tokens
     */
    Token token;

    /**
     * Available expression objects
     */
    List<Expression> expObjs;

    /**
     * Constructs a new Scanner
     * @param context the scanner context
     */
    public SimpleScanner(ScannerContext context) {
        super(context);
        expObjs = new ArrayList();
        expObjs.add(new IdExpression());
        expObjs.add(new NumExpression());
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public boolean next() throws IOException {
        Token t;
        for(Expression e : expObjs) {
            t = e.interpret(getContext());
            if(t != null) {
                if(availables() == 0)
                    incAvailables();
                token = t;
                return true;
            }
        }
        return false;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Token peek() {
        if(availables() > 0)
            return token;
        return null;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Token get() {
        Token t = null;
        if(availables() > 0) {
            t = token;
            token = null;
            decAvailables();
        }
        return t;
    }

}