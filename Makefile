BRIDGE_DIR=bridge/winelib/steam_api_bridge.dll

.PHONY : all clean install

all :
	cd $(BRIDGE_DIR) && $(MAKE)

clean :
	cd $(BRIDGE_DIR) && $(MAKE) clean

install :
	cd $(BRIDGE_DIR) && ./setup.sh

update :
	cd $(BRIDGE_DIR) && ./update.sh

