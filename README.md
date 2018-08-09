# Word-Chains #
### Project Description ###
The aim of the word chains project was to implement a program to find all longest chains of words formed under certain conditions. This resembles the longest path problem of a directed acyclic graph with the condition that paths must also be returned. For a link to be formed from _word1_ - _word2_ condition 1 must be met as well as at least one of the conditions 2, 3 and 4:

1. _word1_ must precede _word2_ alphabetically.
2. _word2_ can be formed by removing one letter from _word1_.
3. _word2_ can be formed by adding one letter from _word1_.
4. _word2_ can be formed by changing one letter from _word1_.

----
### Demo ###
To demo the project simply run the following commands:

To compile the program use:

`$ make` 

To run the program:

`$ ./wordchains`

After this command there will be a prompt to enter _number_of_words_. Once this is entered there will be _number_of_words_ further prompts to enter each of the words in which a maximal chain/s will be derived from.

To run the program with the supplied input file use:

`$ ./wordchains < input.txt`

----

### Output ###
Provided below is an example interaction:

```
$ ./wordchains
Enter a number: 16
Enter word: ace
Enter word: bars
Enter word: barse
Enter word: bas
Enter word: base
Enter word: basem
Enter word: baso
Enter word: basom
Enter word: brace
Enter word: lace
Enter word: mace
Enter word: place
Enter word: plane
Enter word: planet
Enter word: race
Enter word: trace

ace: lace mace race
bars: barse bas
barse: base
bas: base baso
base: basem baso
basem: basom
baso: basom
basom:
brace: race trace
lace: mace place race
mace: race
place: plane
plane: planet
planet:
race: trace
trace:

Maximum chain length: 5
Maximal chains:
bars -> barse -> base -> basem -> basom
bars -> bas -> base -> basem -> basom
bars -> barse -> base -> baso -> basom
bars -> bas -> base -> baso -> basom
ace -> lace -> place -> plane -> planet
ace -> lace -> mace -> race -> trace
```
