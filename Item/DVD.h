#ifndef DVD_H
#define DVD_H

#include <iostream>
#include <string>

#include "Item.h"

class DVD : public Item {
 protected:
  std::string director;
  int duration;  // in minutes
  std::string media_type;
  bool is_playable;

 public:
  DVD(int id, const std::string& title, bool isAvailable, int num,
      const std::string& director, int duration, const std::string& media_type,
      bool is_playable);

  std::string GetDirector() const;
  int GetDuration() const;
  std::string GetMediaType() const;
  bool CheckPlayable() const;

  void Play() const;

  void DisplayInfo() const override;
  std::string GetType() const override;

  std::string ToCsv() const override;
};

#endif
