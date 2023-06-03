/**
 * 
 * The very simple compiler project, 2018.
 * 
 * Written by Peterson D. de Bem.
 * 
 */

package br.petersonddb.verysimplecompiler.lexicalanalysis;

import java.io.InputStream;
import java.io.InputStreamReader;

import java.io.UnsupportedEncodingException;
import java.io.IOException;

/** 
 * This class defines the scanner context abstraction.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public abstract class ScannerContext {

    /**
     * This is used to read the input stream
     */
    private InputStreamReader reader;

    /**
     * Constructs a new ScannerContext
     * @param input the input to read from
     * @throws UnsupportedEncodingException if the input stream reader does not support UTF-8 charset, this should not happen
     */
    public ScannerContext(InputStream input) throws UnsupportedEncodingException {
        reader = new InputStreamReader(input, "UTF-8");
    }

    /**
     * Read one char from the input
     * @return the read char or -1 if there is nothing to read
     * @throws IOException if an I/O error occurs when reading from the input stream
     */
    public char read() throws IOException {
        return (char) reader.read();
    }

    /**
     * Move back input by one char (this can be implemented using a chars buffer)
     * @return the latest read char
     */
    public abstract char unread();

    /**
     * Returns the current string read from the input
     * @return the current string read from the input
     */
    public abstract String getCurrent();

    /**
     * Prepares to get the next string
     */
    public abstract void rebase();

}