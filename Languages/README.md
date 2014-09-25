Languages
======================

The Enterprise has encountered a planet that at one point had been inhabited. The only
remnant from the prior civilization is a set of texts that was found. Using a small set of keywords
found in various different languages, the Enterprise team is trying to determine what type of beings
inhabited the planet.

Input
======================
The first line of input will be N (1 ≤ N ≤ 100), the number of different known languages. The
next N lines contain, in order, the name of the language, followed by one or more words in that
language, separated with spaces. Following that will be a blank line. After that will be a series of
lines, each in one language, for which you are to determine the appropriate language.

Words consist of uninterrupted strings of upper or lowercase ASCII letters, apostrophes, or
hyphens, as do the names of languages. No words will appear in more than one language.

No line will be longer than 256 characters. There will be at most 1000 lines of sample text.

Every sample text will contain at least one keyword from one of the languages. No sample
text will contain keywords from multiple languages. The sample text may contain additional
punctuation (commas, periods, exclamation points, semicolons, question marks, and parentheses)
and spaces, all of which serve as delimiters separating keywords. Sample text may contain words
that are not keywords for any specific language.

Keywords should be matched in a case-insensitive manner.

Output
===========================
For each line of sample text that follows the blank line separating the defined languages, print a
single line that identifies the language with which the sample text is associated.

Input
=============
4

Vulcan throks kilko-srashiv k’etwel
Romulan Tehca uckwazta Uhn Neemasta
Menk e’satta prah ra’sata
Russian sluchilos

Dif-tor heh, Spohkh. I’tah trai k’etwel
Uhn kan’aganna! Tehca zuhn ruga’noktan!

Sample Output
=================
Vulcan
Romulan

