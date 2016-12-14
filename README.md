# TOPDDT

Skeleton code for TOP DQM development.

## Usage

There are two ways to run this script:

1. Run directly with ROOT:

```
root Main.cpp
```

You can change the input and output filenames in the function `Main()`.

2. Compile first:

```
make
```

then run it with

```
./topddt
```

The program runs much faster in this way. But `gcc` is required for compiling.

## Input file format

This program reads input parameters from a csv file. One example showns below:

```
#number of histos, histo dimension (1D or 2D), class name, name, title, nbinsx, xmin, xmax, (for 2D: nbinsy, ymin, ymax)
1,1,NhitsPlot, hnhits, histograms for nhits, 100, 0, 200
16,1,NhitsPerModulePlot, hnhits_per_module, nhits for each module, 100, 0, 200
```

Each line of this file describes one histogrammer, which includes the number of histograms, the dimension for each histogram (1D or 2D), the class name for the histogrammer, the name, title, number of bins, lower and upper limits for the histograms. Comment lines start with `#`. Input file name can be changed in `Main.cpp`.

## How to write new histogrammer

1. Define a new class which inherits from `Histogrammer` class.
2. Override function `process_event` to process each event and fill the histograms.
3. Include the new file in the beginning of the `Main.cpp`.
4. Add a line similar to the following:
```
		Histogrammer *nh;
		if (class_name=="NhitsPlot") {
			nh=new NhitsPlot();
		} else if (class_name=="NhitsPerModulePlot") {
			nh=new NhitsPerModulePlot();
		}
```

Finally you can define the parameters in the input csv file.

Look at `NhitsPlot.h` and `NhitsPerModulePlot.h` for more implementation details.

