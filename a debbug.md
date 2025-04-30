# debbug

## par fonction :

### lexing:

- `lexer` input = NULL = segfault
- OK `check_unclosed_quotes` en theorie si input = NULL = segfault
- OK `check_unclosed_parentheses` en theorie si input = NULL = segfault
- OK `tokenizing` input = NULL = segfault
  - NON continue est correct - si handle operator return false
- OK `get_quoted_word` DOUBLE_QUOTE, SINGLE_QUOTE inconnu sur le main
  - OK input = NULL = segfault
  - OK guard a strndup
- OK`get_unquoted_word` input = NULL = segfault
  - OK guard a strndup
- OK `handle_word` strjoin = NULL = Leaks
  - OK pas de gestion du cas ou get_unquoted_word ou get_quoted_word sont a NULL
- `add_token` si new_token = null tu free new_token ?
- OK `add_operator` guard aux strndup
- OK `handle_operator` input = NULL = segfault

### env

- `create_env_node` return false ? le retour est en t_env
  - strdup guard
- `set_env_value` strdup guard
  - en cas d'erreur return false mais ne free pas la chaine voulu ??
- `env_delone` tu free mais ne verifie pas que c'est pas a null !node n'empeche pas de !node->type
- `add_env_node` si new = null = bug
- OK `init_env` guard si strdup ou substr
  - ??? rollback si une ligne echoue ?
- OK `get_env_value` ft_itoa(last_exit) ?? pourquoi?? si c'est voulu itoa peut echouer a verifier
- `get_envp` guard strjoin + si echoue rollback

### expansion

- `expand_one_arg` si arg = NULL = segfault
- `handle_regular_char` guard a strjoin
- `expand_variables` si expand_one_arg = NULL pas de gestion d'erreur
  - si probleme dans la boucle pas de rollback (peut etre voulu)
  - doit pas etre un void mais un bool pour pouvoir gere les erreurs
