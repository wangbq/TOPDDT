# TOPDDT

Skeleton code for TOP DQM development.

## Usage

Before run this program, compile it with

```
make
```

Then run it with

```
./topddt
```

## How to Write New Histogrammer

NhitHistogrammer could be used as a template to write new histogrammer.

1. Create a new file and include `Main.h` in the beginning.

2. Write a new class which is the subclass of Histogrammer.

3. In member function `process_event`, write codes to fill histograms.

4. In member function `plot`, create a new `TCanvas` object and plot histograms.

5. In member function `finalize`, save the histograms to output file.

6. Include the new created file in the beginning of `Main.cpp`.

7. Create an object of the new class, and add it to the experiment object in function `Main`, like the following:

```
	NhitHistogrammer *nh=new NhitHistogrammer();
	e.add_histogrammer(nh);
```
