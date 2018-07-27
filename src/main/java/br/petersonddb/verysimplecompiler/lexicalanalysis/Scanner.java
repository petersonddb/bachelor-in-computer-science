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
 * This class defines the Scanner abstraction.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public abstract class Scanner {

    private int availableTokens;
    private ScannerContext context;

    /**
     * Constructs a new Scanner
     * @param context the scanner context
     */
    public Scanner(ScannerContext context) {
        this.context =  context;
    }

    /**
     * Gets the next token from the input and save it into a buffer
     * @return true if there is a next token, false otherwise
     * @throws IOException If an I/O error occurs when reading from the input stream
     */
    public abstract boolean next() throws IOException;

    /**
     * Peeks the latest token added to the buffer
     * @return the latest token found
     */
    public abstract Token peek();

    /**
     * Gets the latest token found and remove it from the buffer
     * @return the latest token found
     */
    public abstract Token get();

    /**
     * Checks how many tokens are in the buffer
     * @return the number of tokens in the buffer
     */
    public int availables() {
        return availableTokens;
    }

    /**
     * Increments the number of available tokens
     */
    public void incAvailables() {
        addAvailables(1);
    }

    /**
     * Adds the specified value to the number of available tokens
     * @param value the value to add to the number of available tokens
     * @throws IllegalArgumentException when available tokens - value lead to a negative number of available tokens
     */
    public void addAvailables(int value) throws IllegalArgumentException {
        int total = availableTokens + value;
        if(total < 0)
            throw new IllegalArgumentException("Value cannot lead to a negative number of available tokens");
        availableTokens = total;
    }

    /**
     * Decrements the number of available tokens
     */
    public void decAvailables() {
        addAvailables(-1);
    }

    /**
     * Returns this scanner's scanner context
     * @return the scanner context
     */
    public ScannerContext getContext() {
        return context;
    }

}