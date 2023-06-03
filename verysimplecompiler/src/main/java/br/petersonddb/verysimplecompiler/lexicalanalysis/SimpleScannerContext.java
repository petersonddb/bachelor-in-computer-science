/**
 * 
 * The very simple compiler project, 2018.
 * 
 * Written by Peterson D. de Bem.
 * 
 */

package br.petersonddb.verysimplecompiler.lexicalanalysis;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import java.io.UnsupportedEncodingException;
import java.io.IOException;

/** 
 * This class defines the simple scanner context.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public class SimpleScannerContext extends ScannerContext {

    /**
     * A buffer to store some part of the read input
     */
    private final List<Character> inputBuffer;

    /**
     * This is used to keep track of the current read input
     */
    private int base, cur;

    /**
     * Constructs a new SimpleScannerContext
     * @param input the input to read from
     * @throws UnsupportedEncodingException if the input stream reader does not support UTF-8 charset, this should not happen
     */
    public SimpleScannerContext(InputStream input) throws UnsupportedEncodingException {
        super(input);
        inputBuffer = new ArrayList();
        rebase();
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public char read() throws IOException {
        char c;
        if(cur < inputBuffer.size() - 1)
            c = inputBuffer.get(cur++);
        else {
            c = super.read();
            if(c != (char) -1) {
                inputBuffer.add(c);
                ++cur;
            }
        }
        return c;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public char unread() {
        char c;
        if(inputBuffer.size() > 0)
            c = inputBuffer.get(--cur);
        else
            c = (char) -1;
        return c;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public String getCurrent() {
        StringBuilder str;
        int c;
        if(inputBuffer.size() > 0 && base < cur) {
            str  = new StringBuilder(); 
            c = base;
            while(c < cur)
                str.append(inputBuffer.get(c++));
        }
        else
            return null;
        return str.toString();
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void rebase() {
        base = cur;
    }

}