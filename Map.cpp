#include "Map.h"

Map::Map()
{
	tmxMap = new Tmx::Map();
	loadMap();
}

void Map::loadMap()
{
	// Just an example
	//tmxMap->ParseFile("./example/example.tmx");

	tmxMap->ParseFile("./example/level1.tmx");

	// Load tilesets
	for (int i = 0; i < tmxMap->GetNumTilesets(); i++) {
		// Get a tileset.
		const Tmx::Tileset *tileset = tmxMap->GetTileset(i);

		// Print tileset information.
		string s = tileset->GetName();
		string source = tileset->GetImage()->GetSource();
		cout << s << " is da name";
		cout << source << " is da filename\n";
		Services::resourceManager()->loadTexture(s, source);
	}


}

Map::~Map()
{
	// Unload the textures used:


	// Delete map
	delete tmxMap;
}

void Map::draw()
{
	// just draw from 0, 0 for now.
	//printf("OD");
	// Iterate through the layers.
	cout << "Layers: " << tmxMap->GetNumLayers() << endl;
	for (int i = 0; i < tmxMap->GetNumLayers(); ++i) {
		cout << "Layer " << i << endl;
		const Tmx::Layer *layer = tmxMap->GetLayer(i);

		for (int y = 0; y < 5; y++){ //layer->GetHeight() - 1; y++) {//layer->GetHeight(); ++y) {
			for (int x = 0; x<5;x++){ //< layer->GetWidth() - 1; x++) {

				// Find a tileset for that id.
				int tileId = //layer->GetTileId(x, y);
					layer->GetTile(x, y).id;
				if (tileId == 0) continue;
				int tilesetIndex = layer->GetTile(x, y).tilesetId;
				//cout << "Current ID: " << tileId << endl;
				//int index = tmxMap->FindTilesetIndex(tileId);
				//cout << "tileset Index? " << tilesetIndex;

				const Tmx::Tileset *tileset = tmxMap->GetTileset(tilesetIndex);

				if (tileset == NULL) continue;

				//cout << tileset->GetFirstGid() << " is first" << endl;
				// I think the tileIDs start at 1.
				//const Tmx::Tileset* what = tmxMap->FindTileset(1);
				//cout << what->GetName() << " is wat" << endl;
				//cout << "Tileset name: " << tileset->GetName() << endl;
				Texture *t = Services::resourceManager()->getTexture(tileset->GetName());

				int tileWidth = tileset->GetTileWidth();
				int tileHeight = tileset->GetTileHeight();
				int firstGid = tileset->GetFirstGid();

				int margin = tileset->GetMargin();
				int spacing = tileset->GetSpacing();
				int width = tileset->GetImage()->GetWidth();
				int height = tileset->GetImage()->GetHeight();

				int columns = ( width - (2 * margin) + spacing) / (tileWidth + spacing);
				int rows = (height - (2 * margin) + spacing) / (tileHeight + spacing);

				//cout << "columns: " << columns << ", rows: " << rows << endl;
				//cout << "TileID: " << tileId << endl;

				// With arbitrarily large numbers, would it work?
				// You might need to rethink this a bit?
				// NVM I figured it out, there's an off-by-one error
				// in which you have to only remove the (firstID - 1)

				//cout << "tileId - firstGid: " << (tileId - firstGid) << endl;

				int basicRow = tileId / columns; //(tileId - (firstGid - 1)) / columns; // is y
				int basicCol = tileId % columns; //(tileId - (firstGid - 1)) % columns; // is x

				//cout << "basic coord: (" << basicCol << ", " << basicRow << ")" << endl;

				int texY = basicRow*tileHeight + margin + basicRow*spacing;
				int texX = basicCol*tileWidth + margin + basicCol*spacing;

				//cout << texX << ", " << texY << endl;


				//t->draw(row, col, 32, 32, x * 32, y * 32);
				//t->draw(texX, texY, 32, 32, x * 32, y * 32);
				t->draw(texX, texY, 128, 128, x * 128, y * 128);
				//(layer->IsTileFlippedHorizontally(x, y)){
				//t->draw(0, 0);
				//t->draw(0, 0, width, height, 0, 0);
			}
		}
	}


}