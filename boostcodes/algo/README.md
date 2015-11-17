algo
====

**Project for the learning and practicing basic and advanced algorithms and data structures.**

```
procedure bfs(G, s):
	Q := queue containing only s
	while Q not empty
		v := Q.front(); Q.remove front()
		for w in G.neighbors(v):
			if w not seen:
				mark w seen
				Q.enqueue(w)
```

```
procedure dfs(G, s):
	S := stack containing only s
	while S not empty
		v := S.pop()
		if v not visited:
			mark v visited
			for w in G.neighbors(v):
				S.push(w)
```

To write a book called "algorithm notes: elegant implementation"!

Resource
--------
[clrs][01]
[a learner's (skanev) solutions of clrs][02]
[algorithm design manual 2nd][03]
[algorithms 4th][04]
[sorting algorithms][05]
[big O][06]
[GSL][07]
[LEDA][08]
[Programming Challenges (OJ)][09]
[Google Code Jam][10]
[cmu algorithm course][11]
[Element of Programming Interview Questions][12]
[Knuth's Home Page][99]

[01]: http://mitpress.mit.edu/books/introduction-algorithms
[02]: http://clrs.skanev.com/index.html
[03]: http://www.algorist.com
[04]: http://algs4.cs.princeton.edu/home
[05]: http://www.sorting-algorithms.com
[06]: http://bigocheatsheet.com
[07]: http://www.gnu.org/software/gsl
[08]: http://www.algorithmic-solutions.com/index.htm
[09]: http://www.programming-challenges.com
[10]: https://code.google.com/codejam
[11]: http://www.cs.cmu.edu/~ckingsf/class/02713-s13/index.html
[12]: https://code.google.com/p/elements-of-programming-interviews/wiki/Programs
[99]: http://www-cs-faculty.stanford.edu/~uno
