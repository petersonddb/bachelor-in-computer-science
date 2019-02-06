# LpSearch - A Words Dictionary

**Note**: *This is an academic software.*

Words dictionary with a feature to suggest, efficiently, words that complete 
the one the user is typing while he is in a search through the dictionary. 

Implemented as a *trie* - a tree data structure used to store key/value pairs; 
no node in the tree stores the key associated with that node, instead, its position 
in the tree defines the key with which it is associated; all the descendants of a 
node have a common key prefix. 

For this program, the keys are the words and the 
values are their descriptions. Each node in the tree stores a letter from a word. 
Thereby, there are paths from the root down in the tree forming words (keys), and 
different words with the same prefix reusing the common part of these paths. 

![trie](images/trie.svg)

*A trie illustration, author: Booyabazooka (based on PNG image by Deco). Modifications by Superm401.*

The words suggestion feature deepens inside the tree from the node that the 
ascendants store, in correct order from top to bottom, the letters already typed 
by the user in its search.

## Features 

* Management (with persistence) of words and their descriptions;
* Search for descriptions of registered words.

## Requirements

Linux operating system.

## How to compile

From the project root folder, run:

`make`

## How to run

After compiled, yet from the project root folder, run:

`./lpsearch`

## Author

LpSearch was originally created by Peterson Daronch de Bem (Petch) in 2016.

petersondaronch@gmail.com

