#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libsimmetrics.la

#######################################
# Build information for each library

# Sources for libsimmetrics
libsimmetrics_la_SOURCES = 	util.c cost.c tokenizer.c simmetrics.c soundex.c jaro.c levenshtein.c jaro_winkler.c \
							smith_waterman.c smith_waterman_gotoh.c needleman_wunch.c monge_elkan.c block_distance.c \
							euclidean_distance.c cosine_similarity.c dice_similarity.c jaccard_similarity.c matching_coefficient.c \
							overlap_coefficient.c qgrams_distance.c

# Linker options libTestProgram
libsimmetrics_la_LDFLAGS = 

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libsimmetrics_la_CPPFLAGS = -I$(top_srcdir)/include

