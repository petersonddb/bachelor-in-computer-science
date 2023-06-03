/**
 * 
 * The very simple compiler project, 2018.
 * 
 * Written by Peterson D. de Bem.
 * 
 */

package br.petersonddb.verysimplecompiler.test.lexicalanalysis;

import junit.framework.Test;
import junit.framework.TestSuite;

import br.petersonddb.verysimplecompiler.lexicalanalysis.ScannerContext;
import br.petersonddb.verysimplecompiler.lexicalanalysis.SimpleScannerContext;

import java.io.InputStream;
import java.io.UnsupportedEncodingException;

/** 
 * This class defines the simple scanner context tests.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public class SimpleScannerContextTest extends ScannerContextTest {

    /**
     * {@inheritDoc}
     * @return a simple scanner context
     */
    @Override
    public ScannerContext getContext(InputStream input) throws UnsupportedEncodingException {
        return new SimpleScannerContext(input);
    }
    
    /**
     * Test suite
     * @return a test to be executed
     */
    public static Test suite() {
        return new TestSuite(SimpleScannerContextTest.class);
    }

}