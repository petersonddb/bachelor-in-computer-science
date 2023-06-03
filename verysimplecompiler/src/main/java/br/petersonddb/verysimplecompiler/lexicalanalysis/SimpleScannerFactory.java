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
 * This class defines the simple scanner factory.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public class SimpleScannerFactory extends ScannerFactory {

    /**
     * {@inheritDoc}
     * @return a new simple scanner context object
     */
    @Override
    public ScannerContext createScannerContext(InputStream input) throws UnsupportedEncodingException {
        return new SimpleScannerContext(input);
    }

    /**
     * {@inheritDoc}
     * @return a new simple scanner object
     */
    @Override
    public Scanner createScanner(ScannerContext context) {
        return new SimpleScanner(context);
    }

}