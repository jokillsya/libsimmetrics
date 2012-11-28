#ifndef libsimmetrics_H
#define libsimmetrics_H

typedef union {

	float (*custom_metric_func) (const char *, const char *, const void *);
	float (*metric_func) (const char *, const char *);

} metric_function_t;

#endif
