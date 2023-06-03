/**
 * 
 * The very simple compiler project, 2018.
 * 
 * Written by Peterson D. de Bem.
 * 
 */

package br.petersonddb.verysimplecompiler.lexicalanalysis;

import java.io.InputStream;

import java.io.UnsupportedEncodingException;

/** 
 * This class defines the scanner factory abstraction.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public abstract class ScannerFactory {

    /**
     * Creates a new scanner context with the specified input stream
     * @param input the input stream to read from
     * @return the new scanner context object
     * @throws UnsupportedEncodingException if the input stream reader does not support UTF-8 charset, this should not happen
     */
    public abstract ScannerContext createScannerContext(InputStream input) throws UnsupportedEncodingException;

    /**
     * Creates a new scanner with the specified scanner context
     * @param context the scanner context
     * @return the new scanner object
     */
    public abstract Scanner createScanner(ScannerContext context);

}