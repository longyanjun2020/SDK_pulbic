This file is for developer that maintains the documents here.

Markdown file is a new feature of Doxygen. It could be compared with text comparison as Doxygen file. But it is even better that md version is more readable for human.

To trade-off human readability, many hidden convention are used. Here are some examples.

## Extensions ##
For page tagging, a PHP-Markdown extension `{#page1}` is used.
For reference with Doxygen, @ref is used if coding symbol like function or variable name.
For Doxygen document control @doxygen_commands are used, such as \@if \@endif. However some Doxygen commands are not usable or limited in md file. This might be fixed in later Doxygen version but now some experiment has to be conducted. For example,

@ingroup is limited once per .md file.
@internal @endinternal are buggy. Now `@if <session>` is used as work-around.

## COC ##
The file extension .md is used in our project and those files now are not collected with specified main page, subpage structure. Instead, a Code-Over-Convention approach is used. The file name order is as document chapter order in the final output.
