/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-16 14:29:32 by vdeliere          #+#    #+#             */
/*   Updated: 2025-10-16 14:29:32 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_HPP
# define COLORS_HPP

#  include <string>

	// Réinitialisation
	static const std::string RESET = "\033[0m";

	// Couleurs de texte normales
	static const std::string BLACK   = "\033[30m";
	static const std::string RED     = "\033[31m";
	static const std::string GREEN   = "\033[32m";
	static const std::string YELLOW  = "\033[33m";
	static const std::string BLUE    = "\033[34m";
	static const std::string MAGENTA = "\033[35m";
	static const std::string CYAN    = "\033[36m";
	static const std::string WHITE   = "\033[37m";

	// Couleurs "bright" (plus claires)
	static const std::string BRIGHT_BLACK   = "\033[90m";
	static const std::string BRIGHT_RED     = "\033[91m";
	static const std::string BRIGHT_GREEN   = "\033[92m";
	static const std::string BRIGHT_YELLOW  = "\033[93m";
	static const std::string BRIGHT_BLUE    = "\033[94m";
	static const std::string BRIGHT_MAGENTA = "\033[95m";
	static const std::string BRIGHT_CYAN    = "\033[96m";
	static const std::string BRIGHT_WHITE   = "\033[97m";

	// Couleurs de fond
	static const std::string BG_BLACK   = "\033[40m";
	static const std::string BG_RED     = "\033[41m";
	static const std::string BG_GREEN   = "\033[42m";
	static const std::string BG_YELLOW  = "\033[43m";
	static const std::string BG_BLUE    = "\033[44m";
	static const std::string BG_MAGENTA = "\033[45m";
	static const std::string BG_CYAN    = "\033[46m";
	static const std::string BG_WHITE   = "\033[47m";

#endif