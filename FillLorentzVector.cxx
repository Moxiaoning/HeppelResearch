
	
void FillLorentzVector()
{
	const Int_t size = 40;
	Float_t energy[size], px[size], py[size], pz[size], E_tot = 0, Pt_tot = 0, Pz_tot = 0;
 	Int_t traj;
	TFile *lorentzfile = TFile::Open("ExampleTree.root");
	TLorentzVector *v1 = new TLorentzVector[size];
	
	TTree *fourVectorTree = (TTree*) lorentzfile->Get("testtree");
	fourVectorTree->SetBranchAddress("energy", energy);
	fourVectorTree->SetBranchAddress("px", px);
	fourVectorTree->SetBranchAddress("py", py);
	fourVectorTree->SetBranchAddress("pz", pz);
	fourVectorTree->SetBranchAddress("nsaved_traj", &traj); 
	Int_t entries = fourVectorTree->GetEntries();
	for(int iEntry = 0; iEntry < entries; iEntry++)
	{	
		fourVectorTree->GetEntry(iEntry);

		for(int iParticle = 0; iParticle < traj; iParticle++)
		{
			v1[iParticle + 1].SetPxPyPzE(px[iParticle], py[iParticle], pz[iParticle], energy[iParticle]);
			v1[iParticle + 1].Print();
			E_tot += energy[iParticle];
			Pz_tot += pz[iParticle];
			Pt_tot += v1[iParticle].Pt();
		}
		
	}
	v1[0].SetPxPyPzE(Pt_tot, 0, Pz_tot, E_tot);
	v1[0].Print();
	TBranch *lorentzBranch = fourVectorTree->Branch("lorentzBranch", v1);
	
	
	
}

