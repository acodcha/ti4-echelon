#pragma once

#include "Include.hpp"

namespace TI4Echelon {

/// \brief Anonymous namespace.
namespace {

std::string date_and_time(const std::tm* date_and_time) noexcept {
  const int year{date_and_time->tm_year + 1900};
  const int month{date_and_time->tm_mon + 1};
  const int day{date_and_time->tm_mday};
  const int hours{date_and_time->tm_hour};
  const int minutes{date_and_time->tm_min};
  const std::string year_string{std::to_string(year)};
  const std::string month_string{month < 10 ? "0" + std::to_string(month) : std::to_string(month)};
  const std::string day_string{day < 10 ? "0" + std::to_string(day) : std::to_string(day)};
  const std::string hours_string{hours < 10 ? "0" + std::to_string(hours) : std::to_string(hours)};
  const std::string minutes_string{minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes)};
  return year_string + "-" + month_string + "-" + day_string + " " + hours_string + ":" + minutes_string;
}

} // namespace

std::string current_local_date_and_time() noexcept {
  const std::time_t number{std::time(0)};
  const std::tm* current{std::localtime(&number)};
  return date_and_time(current);
}

std::string current_utc_date_and_time() noexcept {
  const std::time_t number{std::time(0)};
  const std::tm* current{std::gmtime(&number)};
  return date_and_time(current) + " UTC";
}

} // namespace TI4Echelon
