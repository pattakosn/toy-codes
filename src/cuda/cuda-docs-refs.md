# Reference documentation links
* [cuda toolkit doc](https://docs.nvidia.com/cuda/)
* [nvcc cuda copiler driver](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html
* [CUDA C++ Programming guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#)
* [CUDA toolkit doc runtime API](https://docs.nvidia.com/cuda/cuda-runtime-api/index.html)
* [CUDA toolkit doc driver API](https://docs.nvidia.com/cuda/cuda-driver-api/driver-vs-runtime-api.html#driver-vs-runtime-api)

# nvidia architecture generations [found here](https://arnon.dk/matching-sm-architectures-arch-and-gencode-for-various-nvidia-cards/)

| Fermi† | Kepler† | Maxwell‡ | Pascal | Volta | Turing | Ampere | Ada (Lovelace) | Hopper|
|--------|---------|----------|--------|-------|--------|--------|----------------|-------|
| sm\_20 | sm\_30  |  sm\_50  | sm\_60 | sm\_70| sm\_75 | sm\_80 | sm\_89         | sm\_90|
|        | sm\_35  |  sm\_52  | sm\_61 |sm\_72(Xavier)| | sm\_86 |        | sm\_90a (Thor)|
|        | sm\_37  |  sm\_53  | sm\_62 |                | sm\_87(Orin)|           |       |

† Fermi and Kepler are deprecated from CUDA 9 and 11 onwards
‡ Maxwell is deprecated from CUDA 11.6 onwards

* Fermi
    - CUDA 3.2 until CUDA 8
    - Deprecated from CUDA 9
    - support completely dropped from CUDA 10.

    *SM20 or SM\_20, compute\_30*
        GeForce 400, 500, 600, GT-630.

* Kepler
    - CUDA 5 until CUDA 10
    - Deprecated from CUDA 11.

    - *SM30 or SM\_30, compute\_30*
        - Kepler architecture (e.g. generic Kepler, GeForce 700, GT-730).
        - Adds support for unified memory programming
        - Completely dropped from CUDA 11 onwards.
    
    - *SM35 or SM\_35, compute\_35*
        - Tesla K40
        - Adds support for dynamic parallelism.
        - Deprecated from CUDA 11, will be dropped in future versions.
    - *SM37 or SM\_37, compute\_37*
        - Tesla K80
        - Adds a few more registers
        - Deprecated from CUDA 11, will be dropped in future versions

* Maxwell
    - CUDA 6 until CUDA 11

    - *SM50 or SM\_50, compute\_50*
        - Tesla/Quadro M series
        - Deprecated from CUDA 11, will be dropped in future versions
    - *SM52 or SM\_52, compute\_52*
        - Quadro M6000, GeForce 900, GTX-970, GTX-980, GTX Titan X
    - *SM53 or SM\_53, compute\_53*
        - Tegra (Jetson) TX1 / Tegra X1, Drive CX, Drive PX, Jetson Nano

* Pascal
    - CUDA 8+

    - *SM60 or SM\_60, compute\_60*
        - Quadro GP100, Tesla P100, DGX-1 (Generic Pascal)
    SM61 or SM_61, compute_61–
    GTX 1080, GTX 1070, GTX 1060, GTX 1050, GTX 1030 (GP108), GT 1010 (GP108) Titan Xp, Tesla P40, Tesla P4, Discrete GPU on the NVIDIA Drive PX2
    SM62 or SM_62, compute_62 – 
    Integrated GPU on the NVIDIA Drive PX2, Tegra (Jetson) TX2

* Volta
    - CUDA 9+

    - *SM70 or SM\_70, compute\_70*
        - DGX-1 with Volta, Tesla V100, GTX 1180 (GV104), Titan V, Quadro GV100
    - *SM72 or SM\_72, compute\_72*
        - Jetson AGX Xavier, Drive AGX Pegasus, Xavier NX

* Turing
    - CUDA 10+

    - *SM75 or SM\_75, compute\_75*
        - GTX/RTX Turing – GTX 1660 Ti, RTX 2060, RTX 2070, RTX 2080, Titan RTX, Quadro RTX 4000, Quadro RTX 5000, Quadro RTX 6000, Quadro RTX 8000, Quadro T1000/T2000, Tesla T4

* Ampere 
    - CUDA 11.1+

    - *SM80 or SM\_80, compute\_80*
        - NVIDIA A100 (the name “Tesla” has been dropped – GA100), NVIDIA DGX-A100
    - *SM86 or SM\_86, compute\_86*
        - Tesla GA10x cards, RTX Ampere – RTX 3080, GA102 – RTX 3090, RTX A2000, A3000, RTX A4000, A5000, A6000, NVIDIA A40, GA106 – RTX 3060, GA104 – RTX 3070, GA107 – RTX 3050, RTX A10, RTX A16, RTX A40, A2 Tensor Core GPU
    - *SM87 or SM\_87, compute\_87* (CUDA 11.4+, introduced with PTX ISA 7.4 / Driver r470 and newer) for Jetson AGX Orin and Drive AGX Orin only

    [“Devices of compute capability 8.6 have 2x more FP32 operations per cycle per SM than devices of compute capability 8.0. While a binary compiled for 8.0 will run as is on 8.6, it is recommended to compile explicitly for 8.6 to benefit from the increased FP32 throughput.“](https://docs.nvidia.com/cuda/ampere-tuning-guide/index.html#improved_fp32)

* Lovelace
    - CUDA 11.8+

    - *SM89 or SM\_89, compute\_89*
        - NVIDIA GeForce RTX 4090, RTX 4080, RTX 6000, Tesla L40

* Hopper
    - CUDA 12+

    - *SM90 or SM\_90, compute\_90*
        - NVIDIA H100 (GH100)
    - *SM90a or SM\_90a, compute\_90a* for PTX ISA version 8.0
       - adds acceleration for features like wgmma and setmaxnreg. This is required for NVIDIA CUTLASS

