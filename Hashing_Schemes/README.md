# Hashing Schemes Research Paper
This a paper that explores and compares the performance of chaining vs open addressing with linear probing

This was an assigment for the UVic class csc226 with Bill Bird as the Prof, algorithms and data structures II

Grade: 100%

Feedback:
---
This is very thorough combination of theoretical prediction and experimental analysis. It is clear from the description of the experiment that alot of effort was invested in creating a robust and reproducible experiment. The use of the standardized hash function from libstdc++ was a good idea.

The analysis (both theoretical and experimental) was strong and well justified. The presentation of experimental data was not optimal (it's hard for a reader to decipher the salient information in Figure 3 since the column headings are not very descriptive). 

The experiment measured number of memory accesses, but as far as I can tell, this was computed using a synthetic counting method (that is, not by using software instrumentation to literally count accesses to memory). This is fine, but it might induce some limitations.

Limitation 1: Maybe some memory accesses are more costly than others (even on modern hardware which is nominally random access). For example, accessing two adjacent memory locations tends to be faster than accessing two memory locations which are far away (due to caching). This limitation is acknowledged explicitly in the report.

Limitation 2: You defined the number of accesses needed for chaining to be 1 + (number of nodes accessed), which makes sense if reading the entire node (element + pointer to next) is counted as one memory access. But in general, is that a reasonable assumption? That is, if a compound object like a list node can be read in one memory access, couldn't two adjacent table elements also be read in one memory access (thereby speeding up linear probing slightly)? This is mostly a thought experiment; I don't think it had any effect on the validity of the results.

I agree with the justifications in your self assessment, but I don't agree with where each item falls on the rubric. Overall this was an outstanding analysis.

---
