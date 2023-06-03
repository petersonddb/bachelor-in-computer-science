/**
 * 
 * The very simple compiler project, 2018.
 * 
 * Written by Peterson D. de Bem.
 * 
 */

package br.petersonddb.verysimplecompiler.test.lexicalanalysis;

import java.io.UnsupportedEncodingException;

import br.petersonddb.verysimplecompiler.lexicalanalysis.ScannerFactory;
import br.petersonddb.verysimplecompiler.lexicalanalysis.SimpleScannerFactory;
import br.petersonddb.verysimplecompiler.lexicalanalysis.ScannerContext;
import br.petersonddb.verysimplecompiler.lexicalanalysis.SimpleScannerContext;
import br.petersonddb.verysimplecompiler.lexicalanalysis.SimpleScanner;

import junit.framework.TestCase;
import junit.framework.TestSuite;
import junit.framework.Test;

/** 
 * This class defines the scanner factory tests.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public class ScannerFactoryTest extends TestCase {

    /**
     * Fixture
     */
    private ScannerFactory simpleScannerFactory;

    /**
     * {@inheritDoc}
     */
    @Override
    protected void setUp() {
        simpleScannerFactory = new SimpleScannerFactory();
    }

    /**
     * Test suite
     * @return a test to be executed
     */
    public static Test suite() {
        return new TestSuite(ScannerFactoryTest.class);
    }

    /**
     * Tests if the simple scanner factory are creating the correct object types
     * @throws UnsupportedEncodingException if the input stream reader does not support UTF-8 charset, this should not happen
     */
    public void testSimpleScannerFactoryObjects() throws UnsupportedEncodingException{
        ScannerContext scannerContext = simpleScannerFactory.createScannerContext(System.in);
        assertTrue(scannerContext instanceof SimpleScannerContext);
        assertTrue(simpleScannerFactory.createScanner(scannerContext) instanceof SimpleScanner);
    }

}
