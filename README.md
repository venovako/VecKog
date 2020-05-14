# VecKog
The vectorized (AVX-512) batched singular value decomposition algorithm for matrices of order two.

This software is a supplementary material for the paper
arXiv:[2005.?????](https://arxiv.org/abs/2005.????? "Batched computation of the SVDs of order two by the AVX-512 vectorization") \[math.NA\].

## Building

### Prerequisites

A recent Intel C compiler on a 64-bit Linux (e.g., CentOS 7.8) is required; macOS (e.g., Catalina) should also be supported (not tested).
The Intel MKL (Math Kernel Library) is recommended, but another LAPACK library could work with some tweaking.

### Make options

Run ``make`` as follows:
```bash
make [CPU=x200|x64] [NDEBUG=0|1|2|3|4|5] [TEST=0|1|2|3|4|5|6|7] [all|clean|help]
```
where ``CPU`` should be set to ``x64`` for Xeons (default), or to ``x200`` for Xeon Phi KNLs, respectively.
Here, ``NDEBUG`` should be set to the desired optimization level (``3`` is a sensible choice).
If unset, the predefined debug-mode build options will be used.

For testing, ``TEST=0`` builds the vectorized code, and ``TEST=4`` builds the pointwise code.
Adding two to ``TEST`` enables the optional backscaling, while adding one enables the step-by-step printouts.
For example, ``make CPU=x200 NDEBUG=3 clean all`` will trigger a full, release-mode rebuild for the KNLs of the vectorized code only (equivalent to ``TEST=0``).

This work has been supported in part by Croatian Science Foundation under the project IP-2014-09-3670 ([MFBDA](https://web.math.pmf.unizg.hr/mfbda/)).
