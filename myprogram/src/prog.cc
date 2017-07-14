/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * - Neither the name of prim nor the names of its contributors may be used to
 * endorse or promote products derived from this software without specific prior
 * written permission.
 *
 * See the NOTICE file distributed with this work for additional information
 * regarding copyright ownership.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <jsoncpp/json/json.h>
#include <zlib.h>

#include <cassert>
#include <cstdint>
#include <fstream>  //NOLINT
#include <sstream>
#include <vector>

#include "util/LinkedList.h"

#include "model/Vehicle.h"
#include "model/Truck.h"
#include "model/Car.h"

int main(int argc, char** argv) {
  for (int i = 0; i < argc; i++) {
    printf("Arg[%i]: %s\n", i, argv[i]);
  }

  if (argc != 2) {
    fprintf(stderr, "You must specify a settings file\n");
    return -1;
  }

  char* configFile = argv[1];
  Json::Value settings;

  std::ifstream is(configFile, std::ifstream::binary);
  if (!is) {
    fprintf(stderr, "Settings error: could not open file '%s'\n", configFile);
    return -1;
  }

  Json::Reader reader;
  bool success = reader.parse(is, settings, true);
  is.close();

  if (!success) {
    fprintf(stderr, "Settings error: failed to parse JSON file '%s'\n",
            configFile);
    fprintf(stderr, "%s\n", reader.getFormattedErrorMessages().c_str());
    return -1;
  }

  printf("################# Settings Start #################\n");
  Json::StyledWriter writer;
  printf("%s\n", writer.write(settings).c_str());
  printf("################# Settings End ###################\n");

  std::vector<Vehicle> trucks;
  std::vector<Vehicle> cars;
  LinkedList<Vehicle> allVehicles;

  Json::Value vehicles = settings["Vehicle"];
  for (unsigned int i = 0; i < vehicles.size(); i++) {
    printf("adding vehicle\n");
    Json::Value vehicle = vehicles[i];
    std::string make = vehicle["make"].asString();
    std::string model = vehicle["model"].asString();
    int year = vehicle["year"].asInt();
    if (vehicle["type"].asString() == "Truck") {
      int bedLength = vehicle["bedLength"].asInt();
      Truck truck(make, model, year, bedLength);
      trucks.push_back(truck);
      allVehicles.push(&truck);
    } else if (vehicle["type"].asString() == "Car") {
      int mpg = vehicle["mpg"].asInt();
      Car car(make, model, year, mpg);
      cars.push_back(car);
      allVehicles.push(&car);
    } else {
      fprintf(stderr, "unknown vehicle type: '%s'\n",
              vehicle["type"].asCString());
      return -1;
    }
  }

  printf("you initialized %lu vehicles\n", allVehicles.size());

  std::stringstream ss;
  for (auto it = cars.begin(); it != cars.end(); ++it) {
    Vehicle car = (*it);
    printf("Car: %s %s %u\n", car.make().c_str(), car.model().c_str(),
           car.year());
  }
  for (auto it = trucks.begin(); it != trucks.end(); ++it) {
    Vehicle truck = (*it);
    printf("Truck: %s %s %u\n", truck.make().c_str(), truck.model().c_str(),
           truck.year());
  }
  const std::string str = ss.str();
  const char* cstr = str.c_str();
  int64_t slen = str.size();

  printf("%s", str.c_str());;

  gzFile fout = gzopen("vehicles.gz", "wb");
  assert(gzwrite(fout, cstr, slen) == slen);
  gzclose(fout);

  return 0;
}
