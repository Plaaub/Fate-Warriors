#include "Interfaz.h"
#include "../Entrada/Input.h"
#include "../Camara/Camara.h"
using namespace irr;

Interfaz* Interfaz::_instancia=0;

Interfaz* Interfaz::Interfaz_getInstance(){
	if(_instancia==0){
		_instancia= new Interfaz(false,1280,720);
	}
	return _instancia;
}


Interfaz::Interfaz(bool moose, unsigned short width, unsigned short height){
	
	if (!moose) { //irrlicht Interfaz initialization
		_device = createDevice(video::E_DRIVER_TYPE::EDT_OPENGL,
				core::dimension2d<u32>(width, height), 16, false, false, false
				);
				  
		_driver = _device->getVideoDriver();
		_smgr = _device->getSceneManager();
		if (_device == 0) {
			std::cout
					<< "Error: no se pudo crear el dispositivo; inicialización de motor fallida"
					<< std::endl;
		}
		_node = 0;
		_mesh = 0;

		_nodeCounter = -1;
		_meshCounter = -1;

		_direction = 0;
		_zdirection = 0;
		
		_height = height;
		_width = width;


		_then = _device->getTimer()->getTime();
		_micamara = new Camara(_smgr, _device);
		
	}
}

unsigned short Interfaz::Interfaz_cargaCaja(short x, short y, short z) {
	scene::ISceneNode* node;

		node = _smgr->addCubeSceneNode();
		node->setPosition(core::vector3df(x,y,z));
	
	_nodes.push_back(node);
	_nodeCounter++;
	node->setPosition(core::vector3df(x, y, z));
	return (_nodeCounter);
}

/*----cargaModelo----
 *descripcion: carga un modelo descomprimido a partir de una ruta
 *inputs:
 *	rutaModelo -> path al archivo del modelo
 *  x -> coordenada x del modelo
 *  z -> coordenada z del modelo
 */

unsigned short Interfaz::Interfaz_cargaModelo(char* rutaModelo,
		bool emf_lightning, short x, short y, short z) {
	scene::IAnimatedMesh* mesh = _smgr->getMesh(rutaModelo);
	scene::ISceneNode* node;
	if (mesh) {
		_meshes.push_back(mesh); //añadir mesh al vector meshes de la escena
		node = _smgr->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
		if (!emf_lightning) {
			node->setMaterialFlag(video::EMF_LIGHTING, false);
		} else {
			node->setMaterialFlag(video::EMF_LIGHTING, true);
		}
	}
	_nodes.push_back(node);
	_nodeCounter++;
	node->setPosition(core::vector3df(x, y, z));
	return (_nodeCounter);
}

/*----cargaModeloZip----
 *descripcion: carga un modelo comprimido a partir de la ruta del modelo comprimido
 *			 : y su nombre una vez descomprimido
 *inputs:
 *	rutaFile -> path al archivo del modelo comprimido
 *	rutaModelo -> nombre del archivo descomprimido
 *  x -> coordenada x del modelo
 *  z -> coordenada z del modelo
 */

unsigned short Interfaz::Interfaz_cargaModeloZip(char* rutaFile,
		char* rutaModelo, bool emf_lightning, short x, short y, short z) {
	_device->getFileSystem()->addFileArchive(rutaFile);
	_mesh = _smgr->getMesh(rutaModelo);
	std::cout << rutaFile << std::endl;

	if (_mesh) {
		_meshes.push_back(_mesh); //añadir mesh al vector meshes de la escena
		_meshCounter++;
		_node = _smgr->addOctTreeSceneNode(_mesh->getMesh(0), 0, -1, 1024);
	}

	if (!emf_lightning) {
		_node->setMaterialFlag(video::EMF_LIGHTING, false);
	} else {
		_node->setMaterialFlag(video::EMF_LIGHTING, true);
	}
	_nodes.push_back(_node);
	_nodeCounter++;
	_node->setPosition(core::vector3df(x, y, z));
	return (_nodeCounter);

}

unsigned short Interfaz::Interfaz_cargaMapa(char* rutaModelo,
		bool emf_lightning, short x, short y, short z){
	
	scene::IAnimatedMesh* mesh = _smgr->getMesh(rutaModelo);
	scene::IMeshSceneNode* node;
	if (mesh) {
		_meshes.push_back(mesh); //añadir mesh al vector meshes de la escena
		node = _smgr->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
		if (!emf_lightning) {
			node->setMaterialFlag(video::EMF_LIGHTING, false);
		} else {
			node->setMaterialFlag(video::EMF_LIGHTING, true);
		}
	}

	_selector = _smgr->createOctreeTriangleSelector(node->getMesh(), node,
				128);
	node->setTriangleSelector(_selector);
	
	_nodes.push_back(node);
	_nodeCounter++;
	node->setPosition(core::vector3df(x, y, z));
	this->Interfaz_collisionEnable();
	return (_nodeCounter);
	
}

unsigned short Interfaz::Interfaz_cargaMapaZip(char* rutaFile, 
		char* rutaModelo, bool emf_lightning, short x, short y, short z){
	_device->getFileSystem()->addFileArchive(rutaFile);
	_mesh = _smgr->getMesh(rutaModelo);
	scene::IMeshSceneNode* node;

	if (_mesh) {
		_meshes.push_back(_mesh); //añadir mesh al vector meshes de la escena
		_meshCounter++;
		node = _smgr->addOctTreeSceneNode(_mesh->getMesh(0), 0, -1, 1024);
	}

	if (!emf_lightning) {
		node->setMaterialFlag(video::EMF_LIGHTING, false);
	} else {
		node->setMaterialFlag(video::EMF_LIGHTING, true);
	}

	if(node){
		_selector = _smgr->createOctreeTriangleSelector(node->getMesh(), node,
				128);
		node->setTriangleSelector(_selector);
	}
	_nodes.push_back(node);
	_nodeCounter++;
	node->setPosition(core::vector3df(x, y, z));
	this->Interfaz_collisionEnable(); 
	return (_nodeCounter);	
}

unsigned short Interfaz::Interfaz_crearProta(char* rutaModelo,
		bool emf_lightning, short x, short y, short z) {
	if (_mesh) {
		_meshes.push_back(_mesh); //añadir mesh al vector meshes de la escena
		_node = _smgr->addOctTreeSceneNode(_mesh->getMesh(0), 0, -1, 1024);
		if (!emf_lightning) {
			_node->setMaterialFlag(video::EMF_LIGHTING, false);
		} else {
			_node->setMaterialFlag(video::EMF_LIGHTING, true);
		}
	}
	_nodes.push_back(_node);
	_Prota = _node;
	_nodeCounter++;
	_node->setPosition(core::vector3df(x, y, z));
	//_micamara = new camara(_node, _smgr);
	return (_nodeCounter);
}

unsigned short Interfaz::Interfaz_crearProtaZip(char* rutaFile,
		char* rutaModelo, bool emf_lightning, short x, short y, short z) {
	_device->getFileSystem()->addFileArchive(rutaFile);
	_mesh = _smgr->getMesh(rutaModelo);
	if (_mesh) {
		_meshes.push_back(_mesh); //añadir mesh al vector meshes de la escena
		_meshCounter++;
		_node = _smgr->addOctTreeSceneNode(_mesh->getMesh(0), 0, -1, 1024);
	}

	if (!emf_lightning) {
		_node->setMaterialFlag(video::EMF_LIGHTING, false);
	} else {
		_node->setMaterialFlag(video::EMF_LIGHTING, true);
	}
	_nodes.push_back(_node);
	_nodeCounter++;
	_node->setPosition(core::vector3df(x, y, z));
	_Prota = _node;
	_micamara->Camara_setProta(_Prota);
	return (_nodeCounter);
}

scene::ISceneNode* Interfaz::Interfaz_GetProta(){
	return(_Prota);
}

scene::ISceneNode* Interfaz::Interfaz_GetNode(unsigned short id){
	return(_nodes.at(id));
}

void Interfaz::Interfaz_moverModelo(unsigned short id, float x, float y,
		float z) {
	_nodes.at(id)->setPosition(core::vector3df(x, y, z));
}

void Interfaz::Interfaz_moverProta(float x,
		float z) {
	_Prota->setPosition(core::vector3df(x,_Prota->getPosition().Y,z));
}

void Interfaz::Interfaz_Update() {
	_micamara->Camara_Update();
}

void Interfaz::Interfaz_Apagar(){
_device->closeDevice();
}

void Interfaz::Interfaz_collisionEnable() {
	scene::ISceneNodeAnimator* anim;
	for (int i = 0; i < _nodes.size(); i++) {

		core::aabbox3d<f32> box = _nodes.at(i)->getBoundingBox();
		core::vector3df radius = box.MaxEdge - box.getCenter();
		anim = _smgr->createCollisionResponseAnimator(_selector, _nodes.at(i),
				core::vector3df(radius.X, radius.Y, radius.Z), //------------------------------------
				core::vector3df(0, -10, 0), core::vector3df(0, 0, 0));
		_nodes.at(i)->addAnimator(anim);
	}
	anim->drop();
}

Camara* Interfaz::Interfaz_getCamara(){
	return _micamara;
}

void Interfaz::Interfaz_GetCamaraDirection(float &x, float &y, float &z){
	x = _micamara->Camara_getDirection().X;
	y = _micamara->Camara_getDirection().Y;
	z = _micamara->Camara_getDirection().Z;
}

void Interfaz::Interfaz_ProtaCollisionEnable(){
	/*
	_selector = _smgr->createOctreeTriangleSelector(_Prota->getMesh(), q3node,
				128);
	q3node->setTriangleSelector(selector);
	
	scene::ISceneNodeAnimator* anim;
	*/
}

void Interfaz::Interfaz_Render() {
	//std::cout<<"tal cual"<<std::endl;
	_driver->beginScene(true, true, 0);
	_smgr->drawAll();
	_device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)
	_driver->endScene();
}

IrrlichtDevice* Interfaz::Interfaz_getDevice() {
	return (_device);
}

Interfaz::~Interfaz() {
	_device->drop();
}