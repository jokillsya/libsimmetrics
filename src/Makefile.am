#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libsimmetrics.la

####################
# Directories
UTIL_D = $(top_srcdir)/src/util
METR_D = $(top_srcdir)/src/metrics
SIMM_D = $(top_srcdir)/src/simmetrics

####################################
# Sources
UTIL_SRC = 	$(UTIL_D)/cost.c \
			$(UTIL_D)/tokenizer.c \
			$(UTIL_D)/util.c 
			
METR_SRC = 	$(METR_D)/soundex.c \
			$(METR_D)/jaro.c \
			$(METR_D)/levenshtein.c \
			$(METR_D)/jaro_winkler.c \
			$(METR_D)/smith_waterman.c \
			$(METR_D)/smith_waterman_gotoh.c \
			$(METR_D)/needleman_wunch.c \
			$(METR_D)/monge_elkan.c \
			$(METR_D)/block_distance.c \
			$(METR_D)/euclidean_distance.c \
			$(METR_D)/cosine_similarity.c \
			$(METR_D)/dice_similarity.c \
			$(METR_D)/jaccard_similarity.c \
			$(METR_D)/matching_coefficient.c \
			$(METR_D)/overlap_coefficient.c \
			$(METR_D)/qgrams_distance.c 
			
SIMM_SRC =	$(SIMM_D)/simmetrics.c 

# Sources for libsimmetrics
libsimmetrics_la_SOURCES =	$(UTIL_SRC) $(METR_SRC) $(SIMM_SRC)

# Linker options libTestProgram
libsimmetrics_la_LDFLAGS = 

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libsimmetrics_la_CPPFLAGS = -I$(top_srcdir)/include
