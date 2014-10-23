//
//  GPDSideMenuViewController.m
//  GPSDemo
//
//  Created by James Lee on 5/10/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDSideMenuViewController.h"
#import "TWTSideMenuViewController.h"
#import "GPDSideMenuCell.h"
#import "GPDSearchViewController.h"

static NSString *const kCellReuseIdentifier = @"side_menu_cell";

@interface GPDSideMenuViewController ()

@end

@implementation GPDSideMenuViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self.view setBackgroundColor:[UIColor GPDDarkBlueColor]];
    [self.tableView registerNib:[UINib nibWithNibName:@"GPDSideMenuCell" bundle:nil]
         forCellReuseIdentifier:kCellReuseIdentifier];
}

- (void)viewDidAppear:(BOOL)animated
{
    [self adjustTableInset];
}

- (void)adjustTableInset
{
    CGSize contentSize = self.tableView.contentSize;
    CGSize boundsSize = self.tableView.bounds.size;
    CGFloat yOffset = 0;
    if(contentSize.height < boundsSize.height) {
        yOffset = floorf((boundsSize.height - contentSize.height)/2);
    }
    [self.tableView setContentInset:UIEdgeInsetsMake(yOffset, 0, 0, 0)];
}

#pragma mark UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.viewControllers ? [self.viewControllers count] : 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    GPDSideMenuCell *cell = [self.tableView dequeueReusableCellWithIdentifier:kCellReuseIdentifier];
    UIViewController *vc = [self.viewControllers objectAtIndex:indexPath.row];
    
    [[cell titleLabel] setText:vc.title];
    return cell;
}

#pragma mark UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    UIViewController *vc = [self.viewControllers objectAtIndex:indexPath.row];
    [self setActiveViewController:vc];
}


- (UIStatusBarStyle)preferredStatusBarStyle
{
    return UIStatusBarStyleLightContent;
}

- (void)sideMenuViewControllerWillOpenMenu:(TWTSideMenuViewController *)sideMenuViewController
{

}

- (void)sideMenuViewControllerDidOpenMenu:(TWTSideMenuViewController *)sideMenuViewController
{
    
}

- (void)sideMenuViewControllerWillCloseMenu:(TWTSideMenuViewController *)sideMenuViewController
{
    [self.view endEditing:YES];
    
}

- (void)sideMenuViewControllerDidCloseMenu:(TWTSideMenuViewController *)sideMenuViewController
{
    
}

- (UINavigationController *)activeNavigationStack
{
    UIViewController *navController = self.sideMenuViewController.mainViewController;
    if ([navController isKindOfClass:[UINavigationController class]]) {
        return (UINavigationController *)navController;
    } else {
        return nil;
    }
}

- (void)setActiveViewController:(UIViewController *)vc
{
    if (self.sideMenuViewController.mainViewController == vc.navigationController) {
        [self.sideMenuViewController closeMenuAnimated:YES completion:nil];
        return;
    }
    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:vc];
    nav.navigationBar.translucent = NO;
    [self.sideMenuViewController setMainViewController:nav animated:YES closeMenu:YES];
    
    if ([self.viewControllers containsObject:vc]) {
        NSUInteger i = [self.viewControllers indexOfObject:vc];
        [self.tableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:i inSection:0]
                                    animated:NO
                              scrollPosition:UITableViewScrollPositionNone];
    }
}

#pragma mark UISearchBarDelegate

- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar
{
    [self goToSearchForQuery:searchBar.text];
    searchBar.text = @"";
    [self.tableView deselectRowAtIndexPath:[self.tableView indexPathForSelectedRow] animated:NO];
}

- (void)goToSearchForQuery:(NSString *)query
{
    GPDSearchViewController *vc = [GPDSearchViewController new];
    vc.searchQuery = query;
    [self.sideMenuViewController setMainViewController:[[UINavigationController alloc] initWithRootViewController:vc] animated:YES closeMenu:YES];
}



@end
