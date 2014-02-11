BRIDGE_ROOT=bridge
BRIDGE_DIR=bridge/steam_api_bridge.dll

.PHONY : all clean rebuild winemaker install update

all :
	cd $(BRIDGE_DIR) && $(MAKE)

clean :
	cd $(BRIDGE_DIR) && $(MAKE) clean

rebuild : clean
	cd $(BRIDGE_DIR) && $(MAKE)

winemaker :
	cd $(BRIDGE_ROOT) && ./winemaker.sh

install :
	cd $(BRIDGE_DIR) && ./setup.sh

update :
	cd $(BRIDGE_DIR) && ./update.sh

