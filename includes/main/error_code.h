#ifndef ERROR_CODE_H
# define ERROR_CODE_H

typedef enum e_error {
    SUCCESS = 0,				// La commande s'est exécutée avec succès.
    GENERIC_ERROR = 1,			// Erreur générale ou non spécifiée.
    USAGE_ERROR = 2,			// Mauvaise utilisation de la commande (syntaxe incorrecte).
    MATH_ERROR = 3,				// Erreur mathématique, comme une division par zéro.
    MEMORY_ERROR = 8,			// Erreur de mémoire insuffisante.
    SPECIFIC_ERROR_42 = 42,		// Code d'erreur spécifique utilisé par certains programmes.
    PERMISSION_ERROR = 86,		// Erreur de permission refusée.
    SYNTAX_ERROR = 102,			// Erreur de syntaxe ou de paramètre incorrect.
    COMMAND_NOT_FOUND = 127,	// La commande spécifiée n'a pas été trouvée.
    SIGNAL_ERROR_131 = 131,		// Erreur de signal SIGBUS (10).
    SIGNAL_ERROR_154 = 154,		// Erreur de signal SIGRTMIN (34).
    SIGNAL_ERROR_170 = 170,		// Erreur de signal SIGSTKFLT (16).
    SIGNAL_ERROR_214 = 214,		// Erreur de signal SIGRTMIN+8 (42).
    SIGNAL_ERROR_252 = 252,		// Erreur de signal SIGXCPU (24).
    SIGNAL_ERROR_253 = 253,		// Erreur de signal SIGXFSZ (25).
    WRAPPER_ERROR = 255			// Erreur dans le wrapper de la commande.
} t_error;


typedef enum e_serror {
    SIGINT_ERROR = 130,				// Signal SIGINT (2)
    SIGKILL_ERROR = 137,			// Signal SIGKILL (9)
    SIGSEGV_ERROR = 139,			// Signal SIGSEGV (11)
    SIGTERM_ERROR = 143,			// Signal SIGTERM (15)
    SIGBUS_ERROR = 131,				// Signal SIGBUS (10)
    SIGRTMIN_ERROR = 154,			// Signal SIGRTMIN (34)
    SIGSTKFLT_ERROR = 170,			// Signal SIGSTKFLT (16)
    SIGRTMIN_PLUS_8_ERROR = 214,	// Signal SIGRTMIN+8 (42)
    SIGXCPU_ERROR = 252,			// Signal SIGXCPU (24)
    SIGXFSZ_ERROR = 253				// Signal SIGXFSZ (25)
} t_serror;