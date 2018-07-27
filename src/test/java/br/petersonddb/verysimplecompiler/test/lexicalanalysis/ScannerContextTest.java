/**
 * 
 * The very simple compiler project, 2018.
 * 
 * Written by Peterson D. de Bem.
 * 
 */

package br.petersonddb.verysimplecompiler.test.lexicalanalysis;

import junit.framework.TestCase;

import br.petersonddb.verysimplecompiler.lexicalanalysis.ScannerContext;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;

/** 
 * This class defines the scanner context tests abstraction.
 * @author Peterson D. de Bem
 * @since v-1.0
 */
public abstract class ScannerContextTest extends TestCase {

    /**
     * Gets the scanner context
     * @param input the input flow for the scanner to analyze
     * @return a concrete scanner context
     * @throws UnsupportedEncodingException if the input stream reader does not support UTF-8 charset, this should not happen
     */
    public abstract ScannerContext getContext(InputStream input) throws UnsupportedEncodingException;

    /**
     * Tests the read and unread operation into the specified scanner context
     * @throws UnsupportedEncodingException if the input stream reader does not support UTF-8 charset, this should not happen
     * @throws FileNotFoundException if the input file (/lexicalanalysis/scanner-context-empty-test-file.txt) does not exist or can't be opened
     * @throws IOException if there is a problem to read from the input file (/lexicalanalysis/scanner-context-empty-test-file.txt)
     */
    public void testScannerContextEmptyReadUnread() throws UnsupportedEncodingException, FileNotFoundException, IOException {
        InputStream input = getClass().getResourceAsStream("/lexicalanalysis/scanner-context-empty-test-file.txt");
        ScannerContext context = getContext(input);

        assertEquals(context.read(), (char) -1);
        assertEquals(context.unread(), (char) -1);

        assertEquals(context.read(), (char) -1);
        assertEquals(context.unread(), (char) -1);
        assertEquals(context.read(), (char) -1);

        assertEquals(context.unread(), (char) -1);
        assertEquals(context.read(), (char) -1);

        assertEquals(context.read(), (char) -1);
        assertEquals(context.read(), (char) -1);
        assertEquals(context.unread(), (char) -1);

        assertEquals(context.read(), (char) -1);
        assertEquals(context.unread(), (char) -1);
        assertEquals(context.unread(), (char) -1);
        
        assertEquals(context.read(), (char) -1);
        assertEquals(context.read(), (char) -1);
        assertEquals(context.unread(), (char) -1);
        assertEquals(context.unread(), (char) -1);

    }

}