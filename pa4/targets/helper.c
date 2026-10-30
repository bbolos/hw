#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>

// This file sets up the environment for each target. You can safely ignore it.

// Fall 2020: Increased stack goal to FFFF0000 from BFFF0000 for running the
// targets in a 64-bit VM (with backward compatibility).
#define MAX_PAD 0x100000

int main(int argc, char *argv[], char *envp[])
{
	// Advance stack by a different amount for each student, so answers
	// are unique.
#ifdef STACK_GOAL
	char *stack_goal = (char *) STACK_GOAL;
#else
	char *stack_goal = (char *) 0xFFFF0000 - COOKIE;
#endif

#ifdef MINIASLR
	// Optionally, advance stack pointer by a random amount on each run.
	// Only used for target6.
	unsigned int r;
	getentropy(&r, sizeof(unsigned int));
	stack_goal -= r & 0xFF;
#endif

	// Advancing the stack to a position that's invariant of the size
	// of the arguments and environment.
	char *esp = alloca(0);
	if ((esp < stack_goal) || (esp - stack_goal > MAX_PAD)) {
		fprintf(stderr, "Can't normalize stack position %p to %p\n", esp, stack_goal);
		return 1;
	}
	alloca(esp - stack_goal);

	// Move argv from top of stack to here, and clear envp, to prevent
	// shortcuts.
	char **_argv = alloca(sizeof(char *)*(argc+1));
	_argv[argc] = NULL;
	for (int i=argc-1; i >= 0; i--) {
		size_t len = strlen(argv[i])+1;
		_argv[i] = alloca(len);
		strncpy(_argv[i], argv[i], len);
		memset(argv[i], 0, len);
		argv[i] = NULL;
	}
	argv = NULL;
	char **_envp = alloca(sizeof(char *));
	_envp[0] = NULL;
	for (int i=0; envp[i] != 0; i++) {
		size_t len = strlen(envp[i])+1;
		memset(envp[i], 0, len);
		envp[i] = NULL;
	}
	envp = NULL;

	// Advancing the stack *again* so that the length of thee
	// arguments we just copied doesn't affect esp inside _main.
	stack_goal -= (MAX_PAD>>1);
	esp = alloca(0);
	if ((esp < stack_goal) || (esp - stack_goal > MAX_PAD)) {
		fprintf(stderr, "Can't normalize stack position %p to %p\n", esp, stack_goal);
		return 1;
	}

	alloca(esp - stack_goal);

	// Make it harder to overwrite main's stack frame.
	volatile int canary = 0xB000DEAD;

	int ret = _main(argc, _argv, _envp);

	if (canary != 0xB000DEAD) {
		fprintf(stderr, "Uh oh, the canary is dead.\n" \
				"Don't overwrite the stack frame for main().\n");
	}
	return ret;
}
