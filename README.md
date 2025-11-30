# DNAsequence

Finding Similarity between two DNA sequences of nucleotides using GPU and C++ for extreme processing.

## Overview

This repository provides an efficient solution to compare DNA sequences using GPU acceleration and C++ to achieve high-performance processing. It is aimed at tasks in computational biology, bioinformatics, and genomics where large-scale DNA data analysis is required.

## Features

- **Fast DNA sequence comparison:** Utilizes GPU for parallel computation to rapidly analyze similarities between two DNA sequences.
- **C++ Backend:** Extreme processing speeds through optimized C++ code.
- **Interactive Analysis:** Jupyter Notebook tutorials for step-by-step demonstration and experimentation.
- **Web Visualization:** HTML files for displaying results interactively.

## Getting Started

### Prerequisites

- [CUDA-compatible GPU](https://developer.nvidia.com/cuda-gpus)
- [C++ Compiler](https://gcc.gnu.org/)
- [Python 3.x](https://www.python.org/)
- [Jupyter Notebook](https://jupyter.org/install)

### Installation

Clone this repository:

```bash
git clone https://github.com/joaogcfa/DNAsequence.git
cd DNAsequence
```

### Usage

The main Jupyter Notebooks provided for running and exploring DNA sequence comparison are:

- [`Final Report.ipynb`](https://github.com/joaogcfa/DNAsequence/blob/main/Final_Report.ipynb): This is the principal notebook containing the final report and demonstration of the methodology and results. **Recommended as the main entry point for analysis and experiments.**
- [`Relatorio_Final_col.ipynb`](https://github.com/joaogcfa/DNAsequence/blob/main/Relatorio_Final_col.ipynb): A variant for Google Colab users, enabling cloud-based execution of the analysis pipeline in a Colab environment.
- [`Relatorio Final.ipynb`](https://github.com/joaogcfa/DNAsequence/blob/main/Relatorio%20Final.ipynb): Another version of the final report; for most users, refer to `Relatorio_Final.ipynb` unless you need this specific variant.

To get started:

1. For most recent and complete analysis, open [`Relatorio_Final.ipynb`](https://github.com/joaogcfa/DNAsequence/blob/main/Relatorio_Final.ipynb) in Jupyter Notebook.
2. If you are using Google Colab, use [`Relatorio_Final_col.ipynb`](https://github.com/joaogcfa/DNAsequence/blob/main/Relatorio_Final_col.ipynb).
3. Additional notebooks and files may exist for intermediate or alternative analyses.

Interact with these notebooks to load DNA sequence data, run similarity analysis, and visualize results. Refer to the specific notebook documentation for step-by-step instructions.

## Example

```python
# Inside the notebook
# Load two DNA sequences and compare
seq1 = "ATGCGTACGGT"
seq2 = "ATCCGTACGGA"

# Run similarity analysis (see notebook for details)

# Output
# Similarity Score: 91%
```

## Repository Structure

```
DNAsequence/
├── notebooks/        # Jupyter notebooks for demos and analysis
├── src/              # C++ source code (GPU-enabled)
├── html/             # HTML for results visualization
└── README.md         # Project info
```

## License

This project is licensed under the MIT License.

## Contact

Created by [joaogcfa](https://github.com/joaogcfa).
