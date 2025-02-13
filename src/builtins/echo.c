/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:19:21 by skassimi          #+#    #+#             */
/*   Updated: 2025/02/13 11:26:50 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_var(const char *str) {
    // Remplace les variables d'environnement par leur valeur
    if (str[0] == '$') {
        const char *env_var = getenv(str + 1);  // Récupère la valeur de l'environnement sans le '$'
        return env_var ? strdup(env_var) : strdup("");  // Si la variable existe, la retourner, sinon vide
    }
    return strdup(str);  // Si ce n'est pas une variable, retourne simplement la chaîne
}

int echo(char **argv, int fdout)
{
    int i = 1;
    bool need_newline = true;
    char *str;
    
    if (fdout < 0)
        return (-1);
    
    // Vérifie si l'option -n est présente
    if (argv[i] && strcmp(argv[i], "-n") == 0) {
        need_newline = false;
        i++;
    }

    while (argv[i] != NULL) {
        // Traitement des arguments
        str = argv[i];

        // Si la chaîne commence par un single quote, on cherche la quote fermante
        if (str[0] == '\'') {
            // Affiche tel quel le contenu entre les quotes simples (sans interprétation)
            ft_putstr_fd(str + 1, fdout);  // Ignorer la quote d'ouverture
            str += strlen(str) - 1;  // Avance au dernier caractère
        }
        // Si la chaîne commence par un double quote, on doit traiter l'expansion des variables
        else if (str[0] == '\"') {
            // Affiche tout ce qui est entre double quote en remplaçant les variables
            char *expanded_str = expand_var(str + 1);  // Suppression du " initial
            ft_putstr_fd(expanded_str, fdout);
            free(expanded_str);
        } else {
            // Si ce n'est pas une quote, on traite le texte normalement
            ft_putstr_fd(str, fdout);
        }
        
        // Espaces entre les arguments sauf si on est sur l'option -n
        if (argv[i + 1] != NULL) {
            ft_putstr_fd(" ", fdout);
        }
        i++;
    }

    // Si l'option -n n'est pas donnée, ajoute un retour à la ligne
    if (need_newline) {
        write(fdout, "\n", 1);
    }
    
    return (0);
}



