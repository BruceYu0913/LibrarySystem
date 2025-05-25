#include "DVD.h"

DVD::DVD(int id, const std::string& title, bool isAvailable, int num,
         const std::string& director, int duration,
         const std::string& media_type, bool is_playable)
    : Item(id, title, isAvailable, num),
      director(director),
      duration(duration),
      media_type(media_type),
      is_playable(is_playable) {}

std::string DVD::GetDirector() const { return director; }

int DVD::GetDuration() const { return duration; }

std::string DVD::GetMediaType() const { return media_type; }

bool DVD::CheckPlayable() const { return is_playable; }

void DVD::Play() const {
  if (is_playable) {
    std::cout << "Now playing \"" << title << "\" directed by " << director
              << "...\n";
  } else {
    std::cout << "This DVD is not playable.\n";
  }
}

void DVD::DisplayInfo() const {
  std::cout << "DVD ID: " << id << "\n"
            << "Title: " << title << "\n"
            << "Director: " << director << "\n"
            << "Duration: " << duration << " minutes\n"
            << "Media Type: " << media_type << "\n"
            << "Playable: " << (is_playable ? "Yes" : "No") << "\n"
            << "Available: " << (isAvailable ? "Yes" : "No") << "\n"
            << "Quantity: " << num << "\n"
            << "Type: " << GetType() << "\n";
}

std::string DVD::GetType() const { return "DVD"; }

std::string DVD::ToCsv() const {
  return this->GetType() + "," + 
         std::to_string(id) + "," + 
         title + "," +
         (isAvailable ? "true" : "false") + "," + 
         std::to_string(num) + "," +
         director + "," + 
         std::to_string(duration) + "," + 
         media_type + "," +
         (is_playable ? "true" : "false");
}
