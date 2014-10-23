//
//  GPDPromoViewController.m
//  GPSDemo
//
//  Created by James Lee on 10/14/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDPromoViewController.h"
#import "GPDPromoDetailViewController.h"

@interface GPDPromoViewController ()

@property (strong, nonatomic) SCSearchFetcher *searchFetcher;
@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (copy, nonatomic) NSArray *perks;
@end

@implementation GPDPromoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.searchFetcher = [[SCSearchFetcher alloc] init];
    self.searchFetcher.listener = self;
    
    SCSearchConstraint *constraints = [[SCSearchConstraint alloc] initWithRadius:999999999
                                                                      maxResults:99
                                                                    maxInstances:1
                                                             supplementalFilters:nil
                                                                   rangedFilters:nil];
    SCSearchSpecs *specs = [[SCSearchSpecs alloc] initWithQuery:@"synchrony_perk"
                                                       location:[SCSearchLocation onlineLocation]
                                                     constraint:constraints
                                                     pagination:nil
                                                         extras:nil];
    [self.searchFetcher fetchList:specs];
}

#pragma mark SCPerkFetcherDelegate
- (void)scPerkFetcher:(SCPerkFetcher *)fetcher fetchedPerk:(SCPerk *)perk forGrpid:(uint64_t)grpid
{
    if ([perk.barcodeUrl length]) {
    }
}

#pragma mark SCSearchFetcherListener

- (void)scSearchFetcher: (SCSearchFetcher *)fetcher fetchedList: (SearchResultList *)list forSpecs: (SCSearchSpecs *)specs
{
    self.perks = list.products;
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.tableView reloadData];
    });
}

- (void)scSearchFetcher: (SCSearchFetcher *)fetcher fetchedNoListForSpecs: (SCSearchSpecs *)specs
{
    
}

#pragma mark UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.perks.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *reuseID = @"perkCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:reuseID];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reuseID];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }
    
    SCSearchResultProduct *perk = self.perks[indexPath.row];
    cell.textLabel.text = perk.productName;
    return cell;
}
#pragma mark UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    SCSearchResultProduct *perk = self.perks[indexPath.row];
    GPDPromoDetailViewController *vc = [GPDPromoDetailViewController new];
    vc.product = perk;
    [self.navigationController pushViewController:vc animated:YES];
}
@end
